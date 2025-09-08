from fastapi import FastAPI
from fastapi.responses import RedirectResponse


app = FastAPI()

@app.get("/")
def root():
    return RedirectResponse(url="/docs")