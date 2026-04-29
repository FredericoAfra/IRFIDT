<h1 align="center">
  🏭 IRFIDT
</h1>

<p align="center">
  <strong>Tracking and management system for materials and products in an industrial environment using RFID tags.</strong>
</p>

<p align="center">
  <img alt="Python" src="https://img.shields.io/badge/Python-3.11+-3776AB?style=flat&logo=python&logoColor=white"/>
  <img alt="FastAPI" src="https://img.shields.io/badge/FastAPI-0.100+-009688?style=flat&logo=fastapi&logoColor=white"/>
  <img alt="SQLite" src="https://img.shields.io/badge/SQLite-003B57?style=flat&logo=sqlite&logoColor=white"/>
  <img alt="ESP32" src="https://img.shields.io/badge/ESP32-RFID-E7352C?style=flat"/>
  <img alt="Status" src="https://img.shields.io/badge/status-em%20desenvolvimento-yellow?style=flat"/>
  <img alt="License" src="https://img.shields.io/badge/license-MIT-green?style=flat"/>
</p>

---

## 📋 Sumário

- [Sobre o Projeto](#-sobre-o-projeto)
- [Arquitetura do Sistema](#-arquitetura-do-sistema)
- [Tecnologias](#-tecnologias)
- [Arquitetura de Pastas](#-arquitetura-de-pastas)
- [Como Rodar Localmente](#-como-rodar-localmente)
- [Endpoints da API](#-endpoints-da-api)
- [Contribuição e Git Flow](#-contribuição-e-git-flow)
- [Roadmap](#-roadmap)
- [Licença](#-licença)

---

## 📖 Sobre o Projeto

A system developed to track and manage the movement of materials and products within an industry. Each item is identified by an **RFID tag**, read by **RC522** sensors connected to **ESP32** microcontrollers installed at strategic points in the factory (entrances, exits, sectors, warehouse, etc.).

When a tag is read, the ESP32 sends the data to a **REST API** (FastAPI), which registers and updates the information in the database. A **web panel** consumes this same API to allow data management and the visualization of dashboards with movement analyses.

### Como funciona na prática

```
[Tag RFID no produto]
        │
        ▼
[Sensor RC522 + ESP32]  ──→  [API FastAPI]  ──→  [Banco SQLite]
    (ponto da fábrica)              │
                                    ▼
                            [Site de Administração]
                         (dashboards + gerenciamento)
```

### ✨ Funcionalidades previstas

- [x] API REST para registro de leituras RFID
- [x] Banco de dados com histórico de movimentações
- [ ] Autenticação e controle de acesso
- [ ] Painel web de administração
- [ ] Dashboards de análise de movimentações
- [ ] Cadastro e gerenciamento de tags, produtos e pontos de leitura

---

## 🏗 Arquitetura do Sistema

O projeto é um **monorepo** dividido em duas partes principais — backend (em desenvolvimento) e frontend (pendente):

| Camada | Tecnologia | Status |
|---|---|---|
| Hardware | ESP32 + Sensor RC522 | ✅ Hardware definido |
| Backend / API | Python + FastAPI | 🔄 Em desenvolvimento |
| Banco de Dados | SQLite | 🔄 Em desenvolvimento |
| Frontend / Painel | A definir | ⏳ Pendente |

---

## 🛠 Tecnologias

| Componente | Tecnologia |
|---|---|
| Linguagem | Python 3.11+ |
| Framework API | FastAPI |
| Banco de Dados | SQLite |
| ORM / Queries | SQLAlchemy / aiosqlite |
| Validação de dados | Pydantic |
| Microcontrolador | ESP32 |
| Sensor RFID | RC522 |
| Comunicação ESP32 → API | `⚠️ A definir` |
| Frontend | `⚠️ A definir` |

> ⚠️ Campos marcados ainda não foram decididos.

---

## 📁 Arquitetura de Pastas

> A estrutura abaixo reflete o estado atual do projeto (backend) e a estrutura planejada para o frontend.

```
nome-do-projeto/
│
├── backend/                        # API REST e banco de dados
│   ├── app/
│   │   ├── api/                    # Rotas e controllers
│   │   │   └── v1/
│   │   │       ├── routes/         # Endpoints organizados por domínio
│   │   │       └── schemas/        # Schemas Pydantic (request/response)
│   │   ├── core/                   # Configurações centrais
│   │   │   ├── config.py           # Variáveis de ambiente e settings
│   │   │   └── database.py         # Conexão com o SQLite
│   │   ├── models/                 # Modelos do banco de dados (ORM)
│   │   ├── services/               # Regras de negócio
│   │   ├── repositories/           # Camada de acesso a dados
│   │   └── main.py                 # Entry point da aplicação
│   ├── tests/                      # Testes da API
│   ├── requirements.txt
│   └── database.db                 # Arquivo SQLite (não versionado)
│
├── frontend/                       # ⏳ Painel web — ainda não iniciado
│
├── firmware/                       # ⏳ Código do ESP32 (opcional incluir no repo)
│
├── .env.example                    # Exemplo de variáveis de ambiente
├── .gitignore
└── README.md
```

> **Nota:** o arquivo `database.db` deve estar no `.gitignore` — nunca versionar o banco de dados.

---

## 🚀 Como Rodar Localmente

### Pré-requisitos

- [Python 3.11+](https://www.python.org/downloads/)

### Instalação

```bash
# 1. Clone o repositório
git clone https://github.com/seu-usuario/nome-do-projeto.git
cd nome-do-projeto/backend

# 2. Crie e ative o ambiente virtual
python -m venv .venv
source .venv/bin/activate       # Windows: .venv\Scripts\activate

# 3. Instale as dependências
pip install -r requirements.txt

# 4. Copie o arquivo de variáveis de ambiente
cp ../.env.example .env

# 5. Suba a API
uvicorn app.main:app --reload
```

A API estará disponível em:
- **API:** `http://localhost:8000`
- **Documentação Swagger:** `http://localhost:8000/docs`
- **Documentação ReDoc:** `http://localhost:8000/redoc`

---

## 📡 Endpoints da API

> Base URL: `http://localhost:8000/api/v1`  
> Documentação interativa completa disponível em `/docs`.

> ⚠️ Os endpoints abaixo refletem o planejamento atual e podem mudar durante o desenvolvimento.

### 📦 Produtos / Materiais

| Método | Endpoint | Descrição | Auth |
|---|---|---|---|
| `GET` | `/products` | Lista todos os produtos cadastrados | ✅ |
| `POST` | `/products` | Cadastra um novo produto | ✅ |
| `GET` | `/products/{id}` | Retorna um produto específico | ✅ |
| `PUT` | `/products/{id}` | Atualiza dados de um produto | ✅ |
| `DELETE` | `/products/{id}` | Remove um produto | ✅ |

### 🏷️ Tags RFID

| Método | Endpoint | Descrição | Auth |
|---|---|---|---|
| `GET` | `/tags` | Lista todas as tags cadastradas | ✅ |
| `POST` | `/tags` | Registra uma nova tag | ✅ |
| `GET` | `/tags/{uid}` | Retorna dados da tag pelo UID | ✅ |
| `PUT` | `/tags/{uid}` | Vincula/atualiza tag a um produto | ✅ |

### 📍 Leituras (eventos dos ESP32)

| Método | Endpoint | Descrição | Auth |
|---|---|---|---|
| `POST` | `/readings` | Registra uma leitura de tag pelo ESP32 | ✅ |
| `GET` | `/readings` | Lista o histórico de leituras | ✅ |
| `GET` | `/readings/{tag_uid}` | Histórico de movimentação de uma tag | ✅ |

### 📊 Movimentações / Dashboard

| Método | Endpoint | Descrição | Auth |
|---|---|---|---|
| `GET` | `/movements` | Lista movimentações com filtros (data, setor) | ✅ |
| `GET` | `/movements/summary` | Resumo agregado para dashboards | ✅ |

---

## 🤝 Contribuição e Git Flow

### Branches

| Branch | Propósito |
|---|---|
| `main` | Código estável — nunca commitar diretamente |
| `develop` | Branch de integração |
| `feature/*` | Novas funcionalidades |
| `fix/*` | Correção de bugs |

### Fluxo de trabalho

```bash
# 1. Atualize o develop local
git checkout develop
git pull origin develop

# 2. Crie sua branch
git checkout -b feature/nome-da-feature

# 3. Commit seguindo Conventional Commits
git commit -m "feat: adiciona endpoint de registro de leitura RFID"

# 4. Envie e abra um Pull Request para develop
git push origin feature/nome-da-feature
```

### Padrão de commits

| Prefixo | Quando usar |
|---|---|
| `feat:` | Nova funcionalidade |
| `fix:` | Correção de bug |
| `docs:` | Documentação |
| `refactor:` | Refatoração sem nova feature |
| `test:` | Testes |
| `chore:` | Build, dependências, CI |

### Versionamento

O projeto segue [Semantic Versioning](https://semver.org/): `MAJOR.MINOR.PATCH`

- `v0.x.x` — fase de desenvolvimento ativo (atual)
- `v1.0.0` — backend e frontend prontos para produção

---

## 🗺 Roadmap

- [x] Estrutura base da API com FastAPI
- [x] Modelagem do banco de dados SQLite
- [ ] Endpoints de produtos, tags e leituras
- [ ] Testes da API
- [ ] Autenticação
- [ ] Frontend — painel de administração
- [ ] Frontend — dashboards de movimentação
- [ ] Integração e testes com ESP32 físico

---

## 📄 Licença

Distribuído sob a licença **MIT**. Veja o arquivo [LICENSE](./LICENSE) para mais detalhes.

---

<p align="center">
  Feito por <a href="https://github.com/seu-usuario">FredericoAfra</a>
</p>
