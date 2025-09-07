const Pages = (function () {
    function loadPage(event, page) {
        if (event) event.preventDefault();

        return fetch(`/pages/${page}`)   // return the promise so we can chain
            .then(response => response.text())
            .then(html => {
                const content = document.getElementById("content");
                content.innerHTML = html;

                // When home.html is loaded, populate the user list
                if (page === 'home.html') {
                    const container = document.getElementById("user-list");
                    if (container) {
                        Users.loadUsers(container);
                    }
                }

            })
            .catch(err => console.error("Failed to load page:", err));
    }

    return { 
        loadPage };
})();
