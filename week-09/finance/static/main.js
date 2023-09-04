/* Calculate total portfolio value */
// Get all stock totals
const stock_totals = document.querySelectorAll(".portfolio-totals");
// Convert node list to array
let stock_totals_arr = [...stock_totals]
// Make a sum of values
let total = 0;
stock_totals_arr.forEach(function(current){
    if(current.innerText != "undefined"){
        total += parseFloat(current.innerText.replace(",","").slice(1));
    }
})

// Get user's cash value
const cash = parseFloat(document.querySelector("#portfolio-cash").innerText.replace(",","").slice(1));

// Add cash to total
total += cash;

// Update totals field
document.querySelector('#portfolio-total').innerText = total.toFixed(2);

