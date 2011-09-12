//Function to get an Array of integers from a Google Spreadsheet
int[] getNumbers() {
    println("Asking Google for numbers...");
    sm = new SimpleSpreadsheetManager();
    sm.init("RandomNumbers", googleUser, googlePass);
    sm.fetchSheetByKey(sUrl, 0);
    
    int n = sm.currentListEntries.size();
    int[] returnArray = new int[n];
    for (int i = 0; i < n; i++) {
        returnArray[i] = int(sm.getCellValue("Number", i));
    }
    println("Got " + n + " numbers.");
    return(returnArray);
}

//Function to generate a random list of integers
int[] getRandomNumbers(int c) {

    int[] returnArray = new int[c];
    for (int i = 0; i < c; i++) {
        returnArray[i] = ceil(random(0,99));
    }
    return(returnArray);
}
