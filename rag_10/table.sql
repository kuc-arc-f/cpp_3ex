CREATE TABLE IF NOT EXISTS document (
  id TEXT PRIMARY KEY,
  sessid TEXT,
  name TEXT,
  content TEXT,
  embeddings BLOB
);

PRAGMA journal_mode = WAL;
