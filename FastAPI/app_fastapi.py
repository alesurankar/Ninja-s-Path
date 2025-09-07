from fastapi import FastAPI, HTTPException
from fastapi.responses import RedirectResponse
from app_utils import init_db, create_user, verify_user, list_users, delete_user
from pydantic import BaseModel
from fastapi.responses import FileResponse
from fastapi.staticfiles import StaticFiles
from pathlib import Path


BASE_DIR = Path(__file__).resolve().parent

app = FastAPI(title="User Management API")

def file_response_no_cache(path):
    headers = {
        "Cache-Control": "no-store, no-cache, must-revalidate, max-age=0",
        "Pragma": "no-cache",
    }
    return FileResponse(path, headers=headers)

class UserRequest(BaseModel):
    username: str

# Mount a "static" directory to serve files from it
app.mount("/static", StaticFiles(directory=BASE_DIR / "static"), name="static")

# --- Initialize DB at startup ---
init_db()

# Endpoints
@app.get("/")
def root():
    return file_response_no_cache(BASE_DIR / "template" / "main.html")

@app.get("/pages/{page_name}")
def get_page(page_name: str):
    file_path = BASE_DIR / "template" / "pages" / page_name
    if file_path.exists():
        return file_response_no_cache(file_path)
    else:
        raise HTTPException(status_code=404, detail="Page not found")

@app.post("/signup")
def signup(user: UserRequest):
    try:
        create_user(user.username)
        return {"message": f"User '{user.username}' created successfully."}
    except Exception as e:
        raise HTTPException(status_code=400, detail=str(e))

@app.post("/login")
def login(user: UserRequest):
    if not verify_user(user.username):
        raise HTTPException(status_code=400, detail=f"User '{user.username}' not found.")
    # Create a TXT file on disk
    filename = "../username.txt"
    with open(filename, "w") as f:
        f.write(user.username)
    return {"message": f"Logged in as '{user.username}', file '{filename}' created."}

@app.get("/users")
def get_users():
    users = list_users()
    return {"users": users}

@app.delete("/users/{username}")
def remove_user(user: UserRequest):
    if delete_user(user.username):
        return {"message": f"User '{user.username}' deleted successfully."}
    raise HTTPException(status_code=400, detail=f"User '{user.username}' not found.")