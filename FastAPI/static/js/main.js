// Initialize everything after page load
window.addEventListener('DOMContentLoaded', () => {
    Pages.loadPage(null, 'home.html').then(() => {
        // Load users list
        const userList = document.getElementById("user-list");
        if (userList) Users.loadUsers(userList);

        // Bind forms
        Users.initInputForm("login-form", "login-message", "login", "POST", "login-username");
        Users.initInputForm("signup-form", "signup-message", "signup", "POST", "signup-username");
        Users.initInputForm("delete-form", "delete-message", "delete-user", "DELETE", "delete-username");
    });
});