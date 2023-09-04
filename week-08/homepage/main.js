/* Footer date */
const footerDate = document.querySelector(".footer_date");
footerDate.innerHTML = new Date().getFullYear() + ".";

/* Form popup */
const form = document.querySelector("form");
form.addEventListener("submit", function(e) {
 alert("This went nowhere. Have a nice day!")
 e.preventDefault();
})