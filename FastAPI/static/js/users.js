const Users = (function () {
    // Public function: load users into a given container
    function loadUsers(container) {
        fetch("/users")
            .then(response => response.json())
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

    // Expose only loadUsers
    return {
        loadUsers
    };
})();
