const Users = (function () {
    // Load users into a container
    function loadUsers(container) {
        fetch("/users")
            .then(res => res.json())
            .then(data => {
                container.innerHTML = "";
                if (data.users && data.users.length > 0) {
                    const ul = document.createElement("ul");
                    data.users.forEach(user => {
                        const li = document.createElement("li");
                        li.textContent = user;
                        ul.appendChild(li);
                    });
                    container.appendChild(ul);
                } else {
                    container.textContent = "No users found";
                }
            })
            .catch(err => {
                console.error("Error fetching users:", err);
                container.textContent = "Failed to load users";
            });
    }

    // Generalized form handler
    function initInputForm(formId, messageId, endpoint, method = "POST", inputId = "username") {
        const form = document.getElementById(formId);
        const messageDiv = document.getElementById(messageId);
        if (!form) return;

        form.addEventListener("submit", async (e) => {
            e.preventDefault();
            const username = document.getElementById(inputId).value;

            try {
                // Build URL and fetch options
                let url = `http://127.0.0.1:8000/${endpoint}`;
                const fetchOptions = {
                    method: method,
                    headers: {
                        "Content-Type": "application/json",
                    },
                };

                // If DELETE, append username to URL and don't send body
                if (method.toUpperCase() === "DELETE") {
                    url += `/${encodeURIComponent(username)}`;
                } else {
                    fetchOptions.body = JSON.stringify({ username });
                }

                const response = await fetch(url, fetchOptions);
                const data = await response.json();

                if (!response.ok) {
                    throw new Error(data.detail || "Request failed");
                }

                messageDiv.textContent = data.message;
                messageDiv.style.color = "green";

                // Reload user list if container exists
                const userList = document.getElementById("user-list");
                if (userList) loadUsers(userList);

            } catch (err) {
                console.error(err);
                messageDiv.textContent = err.message;
                messageDiv.style.color = "red";
            }
        });
    }

    return { 
        loadUsers, 
        initInputForm 
    };
})();

