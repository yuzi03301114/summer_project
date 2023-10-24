document.addEventListener("DOMContentLoaded", function () {
  // Elements
  var phInput1 = document.getElementById("number1");
  var phInput2 = document.getElementById("number2");
  var updateButton = document.getElementById("update-button");
  var phValue = document.getElementById("ph-value");
  var historyButton = document.getElementById("history-button");
  var historyData = document.getElementById("history-data");
  var historyTable = document
    .getElementById("history-table")
    .getElementsByTagName("tbody")[0];

  // pH history
  var pHHistory = [];

  // Update ph value
  // updateButton.addEventListener("click", function () {
  //   var newPhValue1 = parseFloat(phInput1.value);
  //   if (!isNaN(newPhValue1)) {
  //     phValue1.textContent = newPhValue1.toFixed(1);
  //     pHHistory.push({
  //       time: getCurrentTime(),
  //       value: newPhValue1.toFixed(1),
  //     });
  //   }
  // });

  // Present history
  historyButton.addEventListener("click", function () {
    // clear table
    historyTable.innerHTML = "";

    // add history into table
    pHHistory.forEach(function (data) {
      var row = document.createElement("tr");
      var timeCell = document.createElement("td");
      var valueCell = document.createElement("td");

      timeCell.textContent = data.time;
      valueCell.textContent = data.value;

      row.appendChild(timeCell);
      row.appendChild(valueCell);
      historyTable.appendChild(row);
    });

    // Switch between show and hide history table
    historyData.classList.toggle("hidden");
  });

  // get current time
  function getCurrentTime() {
    var now = new Date();
    var hours = now.getHours();
    var minutes = now.getMinutes();
    var seconds = now.getSeconds();
    var timeString =
      hours.toString().padStart(2, "0") +
      ":" +
      minutes.toString().padStart(2, "0") +
      ":" +
      seconds.toString().padStart(2, "0");
    return timeString;
  }
});
