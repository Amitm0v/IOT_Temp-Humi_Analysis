function doGet(e) {
  var sheet = SpreadsheetApp.openById("11O5kZT8xUngyxpjY5rvWLfcsuYvOTf7_nZyFHULHirU").getActiveSheet(); /paste the key from esp32
  sheet.appendRow([new Date(), e.parameter.temp, e.parameter.hum]);

  return ContentService.createTextOutput("Data added successfully");

}
