from fastapi import FastAPI, HTTPException
from fastapi.responses import RedirectResponse
from app_utils import init_db, create_user, verify_user, list_users, delete_user
from pydantic import BaseModel

app = FastAPI(title="User Management API")


class UserRequest(BaseModel):
    username: str

# --- Initialize DB at startup ---
init_db()

# endpoints
@app.get("/")
def root():
    return RedirectResponse(url="/docs")

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