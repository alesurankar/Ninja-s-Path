import sqlite3


DB_NAME = "data.db"


# --- Database Connection ---
def get_db_connection():
    conn = sqlite3.connect(DB_NAME)
    conn.row_factory = sqlite3.Row
    conn.isolation_level = None 
    return conn


# --- User Table Management ---
def init_db():
    conn = get_db_connection()
    conn.execute("""
        CREATE TABLE IF NOT EXISTS users (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            username TEXT UNIQUE NOT NULL
        )
    """)
    conn.commit()
    conn.close()


# --- Data Manipulation ---
def create_user(username):
    conn = get_db_connection()
    conn.execute("INSERT INTO users (username) VALUES (?)", (username,))
    conn.commit()
    conn.close()

def verify_user(username: str):
    conn = get_db_connection()
    cursor = conn.execute("SELECT id FROM users WHERE username = ?", (username,))
    exists = cursor.fetchone() is not None
    conn.close()
    return exists

def list_users():
    conn = get_db_connection()
    cursor = conn.execute("SELECT username FROM users")
    users = [row["username"] for row in cursor.fetchall()]
    conn.close()
    return users

def delete_user(username: str):
    conn = get_db_connection()
    cursor = conn.execute("DELETE FROM users WHERE username = ?", (username,))
    conn.commit()
    conn.close()
    return cursor.rowcount > 0