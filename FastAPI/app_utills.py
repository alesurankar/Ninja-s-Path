import sqlite3
import re

# --- Utility Functions ---
def get_db_connection():
    conn = sqlite3.connect('data.db')  # Opens (or creates) data.db
    conn.row_factory = sqlite3.Row     # Lets you access rows as dict-like objects
    conn.isolation_level = None        # Enables autocommit mode (commits immediately)
    return conn

def validate_table_name(table_name):
    if not re.match(r'^[a-zA-Z_][a-zA-Z0-9_]*$', table_name):
        raise ValueError("Invalid table name.")


# --- Table Management ---
def create_table(table_name):
    validate_table_name(table_name) # Safety check
    conn = get_db_connection()
    # Create table with only id and name
    conn.execute(f'''
        CREATE TABLE IF NOT EXISTS {table_name} (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            name TEXT
        )
    ''')
    # Optional: insert a default row if table is empty
    cursor = conn.execute(f"SELECT COUNT(*) as count FROM {table_name}")
    count = cursor.fetchone()["count"]
    if count == 0:
        conn.execute(f"INSERT INTO {table_name} (name) VALUES (?)", ("DefaultName",))
    conn.commit()
    conn.close()

def delete_table(table_name):
    validate_table_name(table_name)
    conn = get_db_connection()
    conn.execute(f"DROP TABLE IF EXISTS {table_name}")
    conn.commit()
    conn.close()

def check_table_exists(table_name):
    validate_table_name(table_name)
    conn = get_db_connection()
    cursor = conn.execute(
        "SELECT name FROM sqlite_master WHERE type='table' AND name=?",
        (table_name,)
    )
    exists = cursor.fetchone() is not None
    conn.close()
    return exists

def list_tables():
    conn = get_db_connection()
    cursor = conn.execute(
        "SELECT name FROM sqlite_master WHERE type='table' AND name NOT LIKE 'sqlite_%'"
    )
    tables = [row["name"] for row in cursor.fetchall()]
    conn.close()
    return tables
