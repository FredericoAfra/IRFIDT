-- ============================================================
-- MetalPrime Componentes Ltda.
-- Schema do sistema de rastreamento RFID
-- Banco: SQLite3
--
-- Notas:
--   - SQLite não tem tipo ENUM nativo. Restrições de valores
--     são feitas via CHECK constraint.
--   - UUID é armazenado como TEXT (36 chars com hifens).
--   - DATETIME é armazenado como TEXT no formato ISO 8601:
--     'YYYY-MM-DD HH:MM:SS'
-- ============================================================


-- ------------------------------------------------------------
-- Tabela: leitores
-- Cadastro dos dispositivos RFID físicos (portais, ESP32, etc.)
-- Deve ser populada na configuração inicial da fábrica.
-- ------------------------------------------------------------
CREATE TABLE IF NOT EXISTS leitores (
    leitor_id   TEXT        NOT NULL,
    tipo        TEXT        NOT NULL CHECK (tipo IN (
                                'portal_entrada',
                                'portal_saida',
                                'estacao_tagueamento',
                                'leitor_inventario'
                            )),
    localizacao TEXT        NOT NULL,
    ativo       INTEGER     NOT NULL DEFAULT 1 CHECK (ativo IN (0, 1)),

    PRIMARY KEY (leitor_id)
);


-- ------------------------------------------------------------
-- Tabela: tags
-- Inventário vivo. Cada linha representa um lote/unidade
-- atualmente rastreada no sistema.
-- Criada pelo ESP32 na estação de tagueamento.
-- Atualizada a cada movimentação ou consumo.
-- ------------------------------------------------------------
CREATE TABLE IF NOT EXISTS tags (
    epc             TEXT        NOT NULL,
    sku             TEXT        NOT NULL,
    nome_item       TEXT        NOT NULL,
    categoria       TEXT        NOT NULL CHECK (categoria IN (
                                    'materia_prima',
                                    'wip',
                                    'produto_acabado'
                                )),
    lote            TEXT        NOT NULL,
    quantidade      REAL        NOT NULL CHECK (quantidade >= 0),
    unidade         TEXT        NOT NULL,
    localizacao_atual TEXT      NOT NULL,
    status          TEXT        NOT NULL DEFAULT 'em_estoque' CHECK (status IN (
                                    'em_estoque',
                                    'em_transito',
                                    'em_producao',
                                    'consumido',
                                    'expedido'
                                )),
    tag_pai_epc     TEXT        DEFAULT NULL,
    criada_em       TEXT        NOT NULL DEFAULT (datetime('now')),
    desativada_em   TEXT        DEFAULT NULL,

    PRIMARY KEY (epc),
    FOREIGN KEY (tag_pai_epc) REFERENCES tags (epc)
);


-- ------------------------------------------------------------
-- Tabela: eventos
-- Log de todas as leituras RFID.
-- Alimenta histórico, inventário em tempo real e análises.
-- Nunca deletar registros — é append-only por natureza.
-- ------------------------------------------------------------
CREATE TABLE IF NOT EXISTS eventos (
    evento_id           TEXT    NOT NULL,
    tag_epc             TEXT    NOT NULL,
    leitor_id           TEXT    NOT NULL,
    tipo_evento         TEXT    NOT NULL CHECK (tipo_evento IN (
                                    'entrada',
                                    'saida',
                                    'criacao',
                                    'transformacao',
                                    'inventario'
                                )),
    timestamp           TEXT    NOT NULL DEFAULT (datetime('now')),
    quantidade_snapshot REAL    DEFAULT NULL,
    observacao          TEXT    DEFAULT NULL,

    PRIMARY KEY (evento_id),
    FOREIGN KEY (tag_epc)   REFERENCES tags     (epc),
    FOREIGN KEY (leitor_id) REFERENCES leitores (leitor_id)
);


-- ------------------------------------------------------------
-- Tabela: transformacoes
-- Genealogia de lotes: liga a tag consumida à tag gerada.
-- Criada pelo ESP32 junto com a nova tag, na estação
-- de tagueamento, ao final de um processo de manufatura.
-- ------------------------------------------------------------
CREATE TABLE IF NOT EXISTS transformacoes (
    transformacao_id    TEXT    NOT NULL,
    tag_origem_epc      TEXT    NOT NULL,
    tag_destino_epc     TEXT    NOT NULL,
    quantidade_consumida REAL   NOT NULL CHECK (quantidade_consumida > 0),
    quantidade_gerada   REAL    NOT NULL CHECK (quantidade_gerada > 0),
    linha_producao      TEXT    NOT NULL,
    ordem_producao      TEXT    NOT NULL,
    timestamp           TEXT    NOT NULL DEFAULT (datetime('now')),

    PRIMARY KEY (transformacao_id),
    FOREIGN KEY (tag_origem_epc)  REFERENCES tags (epc),
    FOREIGN KEY (tag_destino_epc) REFERENCES tags (epc)
);


-- ------------------------------------------------------------
-- Índices para consultas frequentes
-- ------------------------------------------------------------

-- Inventário atual: filtrar por status e localização
CREATE INDEX IF NOT EXISTS idx_tags_status
    ON tags (status);

CREATE INDEX IF NOT EXISTS idx_tags_localizacao
    ON tags (localizacao_atual);

-- Histórico de uma tag específica
CREATE INDEX IF NOT EXISTS idx_eventos_tag
    ON eventos (tag_epc);

-- Eventos ordenados por tempo (consultas de auditoria)
CREATE INDEX IF NOT EXISTS idx_eventos_timestamp
    ON eventos (timestamp);

-- Genealogia: encontrar o que foi gerado a partir de uma origem
CREATE INDEX IF NOT EXISTS idx_transformacoes_origem
    ON transformacoes (tag_origem_epc);