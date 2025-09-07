import app_utills

from fastapi import FastAPI, HTTPException
from fastapi.responses import RedirectResponse


app = FastAPI()

@app.get("/")
def root():
    return RedirectResponse(url="/docs")

# --- Table Management ---
@app.post("/create-table/{table_name}")
def api_create_table(table_name: str):
    try:
        app_utills.create_table(table_name)
        return {"message": f"Table '{table_name}' created successfully."}
    except ValueError as e:
        raise HTTPException(status_code=400, detail=str(e))
    

@app.delete("/delete-table/{table_name}")
def api_delete_table(table_name: str):
    try:
        app_utills.delete_table(table_name)
        return {"message": f"Table '{table_name}' deleted successfully."}
    except ValueError as e:
        raise HTTPException(status_code=400, detail=str(e))
    

@app.get("/check-table/{table_name}")
def api_check_table(table_name: str):
    try:
        exists = app_utills.check_table_exists(table_name)
        return {"exists": exists}
    except ValueError as e:
        raise HTTPException(status_code=400, detail=str(e))


@app.get("/list-tables")
def api_list_tables():
    try:
        tables = app_utills.list_tables()
        return {"tables": tables}
    except Exception as e:
        raise HTTPException(status_code=500, detail=str(e))