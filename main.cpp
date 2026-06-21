#include <iostream>
#include <fstream>   
#include <cstdlib>   
#include <sstream>   
#include <map>       
#include <cmath>     

using namespace std;

// The multi-column database structure mapping your retail variables
struct ProductStock {
    int available = 0;       // Current physical count inside the shop
    int benchmark = 0;       // Low-stock safety threshold line
    double cost_price = 0.0;   // What the shopkeeper paid to buy it (CP)
    double selling_price = 0.0;// What the shopkeeper charges customers (SP)
    int units_sold = 0;
    double total_revenue;
        // Total quantity sold over time
};

// Our primary localized data table map
map<string, ProductStock> inventoryTable;

// Saves the entire high-speed memory table onto the Ubuntu disk drive
void saveTableToDisk() {
    ofstream dbFile("database.txt");
    for (auto const& [name, stock] : inventoryTable) {
        dbFile << name << "," 
               << stock.available << "," 
               << stock.benchmark << "," 
               << stock.cost_price << "," 
               << stock.selling_price << ","
               << stock.units_sold << "\n";
    }
    dbFile.close();
}

// Automatically loads database rows back into memory when the terminal boots up
void loadTableFromDisk() {
    ifstream dbFile("database.txt");
    if (!dbFile.is_open()) return; // No file yet, start fresh on first boot

    string line;
    while (getline(dbFile, line)) {
        stringstream ss(line);
        string name, av, bn, cp, sp, us;
        
        getline(ss, name, ','); getline(ss, av, ','); getline(ss, bn, ',');
        getline(ss, cp, ',');   getline(ss, sp, ','); getline(ss, us, ',');

        if(!name.empty()) {
            inventoryTable[name] = { stoi(av), stoi(bn), stod(cp), stod(sp), stoi(us) };
        }
    }
    dbFile.close();
}


void triggerLowStockSMS(string name, int currentStock) {
    cout << "[!] Threshold breached. Initiating real-world cellular transmission link..." << endl;

    // 1. SETUP YOUR CELLULAR ROUTING KEYS
    string account_sid = "PASTE TWILIO ACCOUNT SID";
    string auth_token  = "TWILIO AUTHENTICATION NUMBER";
    string twilio_num  = "TWILIO TRIAL NUMBER"; 
    string my_real_num = "YOUR REAL NUMBER"; // Your personal number with country code

    // 2. CRAFT THE TEXT MESSAGE BODY
    string messageBody = "ALERT: Stock for [" + name + "] is running dangerously low. Current stock count: " + to_string(currentStock);

    // 3. EXECUTE THE APEX NETWORK CALL OVER TWILIO'S REST API
    string command = "curl -X POST \"https://api.twilio.com/2010-04-01/Accounts/" + account_sid + "/Messages.json\" "
                     "--data-urlencode \"Body=" + messageBody + "\" "
                     "--data-urlencode \"From=" + twilio_num + "\" "
                     "--data-urlencode \"To=" + my_real_num + "\" "
                     "-u \"" + account_sid + ":" + auth_token + "\" > sms_receipt.json 2>&1";

    // Run the network payload system shell escape
    int status = system(command.c_str());

    if(status == 0) {
        cout << "[+] Global Cellular Link Connected! SMS successfully dispatched to " << my_real_num << endl;
    } else {
        cout << "[-] Carrier Routing Error. Check connection or credit metrics." << endl;
    }
}



// FEATURE 2: Compiles and displays a comprehensive business profit and loss statement
void generateFinancialReport() {
    double grandTotalCost = 0.0;
    double grandTotalRevenue = 0.0;
    double grandTotalProfit = 0.0;

    cout << "\n=======================================================================================================" << endl;
    cout << "                          SHEETKEEPER AI - SHOP FINANCIAL REPORT                                       " << endl;
    cout << "=======================================================================================================" << endl;
    cout << "  PRODUCT NAME          |  BM (UNITS)  |  CP (Rs)  |  SP (Rs)  |  AVAILABLE  |  UNITS SOLD  |  NET PROFIT  " << endl;
    cout << "------------------------+--------------+-----------+-----------+-------------+--------------+----------" << endl;

    for (auto const& [name, stock] : inventoryTable) {
        double totalCost = stock.units_sold * stock.cost_price;
        double totalRevenue = stock.units_sold * stock.selling_price;
        double netProfit = totalRevenue - totalCost;

        grandTotalCost += totalCost;
        grandTotalRevenue += totalRevenue;
        grandTotalProfit += netProfit;

        // Visual alignment padding logic to keep the console columns clean
        string pName = name; while (pName.length() < 23) pName += " ";
        string bmStr = to_string(stock.benchmark); while (bmStr.length() < 12) bmStr += " ";
        string cpStr = to_string((int)stock.cost_price); while (cpStr.length() < 9) cpStr += " ";
        string spStr = to_string((int)stock.selling_price); while (spStr.length() < 9) spStr += " ";
        string availStr = to_string(stock.available); while (availStr.length() < 11) availStr += " ";
        string soldStr = to_string(stock.units_sold); while (soldStr.length() < 12) soldStr += " ";

        cout << "  " << pName << " | " << bmStr << " | Rs." << cpStr << " | Rs." << spStr << " | " << availStr << " | " << soldStr << " | Rs." << netProfit << endl;
    }

    cout << "-------------------------------------------------------------------------------------------------------" << endl;
    cout << "  TOTAL CAPITAL COST INVESTED : Rs." << grandTotalCost << endl;
    cout << "  TOTAL SALES REVENUE EARNED  : Rs." << grandTotalRevenue << endl;
    cout << "  NET TOTAL BUSINESS PROFIT   : Rs." << grandTotalProfit << endl;
    cout << "=======================================================================================================\n" << endl;
}


// Forward declaration so the mobile sync routine can access the Gemini router smoothly
void sendToGemini(string conversationalInput, string apiKey, string sheetsUrl);

// FEATURE 3: Downloads natural sentences typed into the remote phone app and routes them to AI
void checkCloudUpdatesFromPhone(string webAppUrl, string apiKey) {
    // Run a curl GET request to check the script cache for entries written via mobile phone
    string command = "curl -L -s \"" + webAppUrl + "\" > phone_sync.json";
    system(command.c_str());

    ifstream file("phone_sync.json");
    if (!file.is_open()) return;
    
    stringstream buffer; buffer << file.rdbuf(); string content = buffer.str(); file.close();

    // If there's an unread conversational sentence waiting for us, extract and process it
    if (content.find("no_new_updates") == string::npos && content.find("sentence") != string::npos) {
        size_t textPos = content.find("\"sentence\":\"") + 12;
        size_t textEnd = content.find("\"", textPos);
        string phoneSentence = content.substr(textPos, textEnd - textPos);
        
        cout << "\n[🔄 Phone Cloud Sync] Found new message from phone: \"" << phoneSentence << "\"" << endl;
        
        // Pass the phone's casual English text straight into Gemini!
        sendToGemini(phoneSentence, apiKey, webAppUrl);
        cout << "> " << flush;
    }
}

// Core parsing logic: Packages data payload to JSON, runs curl, extracts tokens, and mutates state
void sendToGemini(string conversationalInput, string apiKey, string sheetsUrl) {
    // Loop through our local memory table map and string-render a text matrix grid for Gemini's context
    string databaseContext = "CURRENT SHOP STATE CONTEXT:\\n";
    for (auto const& [name, stock] : inventoryTable) {
        databaseContext += "- [" + name + "] Available=" + to_string(stock.available) + ", Benchmark=" + to_string(stock.benchmark) + "\\n";
    }

    // Wrap full instructions with the live data matrix
// Wrap full instructions with the live data matrix
    string prompt =  "You are an advanced inventory parsing assistant for a retail shop. Analyze the user's sentence based on this context:\\n" + databaseContext + "\\n"
                "RULES:\\n"
                "1. If they add, buy, restock, or purchase an existing or brand-new item, format exactly: UPDATE,[exact product name],+[quantity]\\n"
                "2. If they sell or dispense an item, format exactly: UPDATE,[exact product name],-[quantity]\\n"
                "3. If they introduce a completely new product to the catalog, format exactly: NEW,[exact product name],[benchmark],[cost_price],[selling_price]\\n"
                "4. If they want to delete, remove, or erase a product entirely from the catalog (e.g., 'delete cpofbread'), format exactly: DELETE,[exact product name]\\n"
                "5. If they report items wasted, spoiled, or damaged (e.g., '5 milk wasted'), format exactly: WASTE,[exact product name],[quantity]\\n"
                "6. If they report an item sold at a specific custom price (e.g., '10 coke sold for 25'), format exactly: CUSTOM_SALE,[exact product name],[quantity],[selling_price]\\n"
                
                "7. For conversational questions, evaluate data context and reply conversationally starting exactly with: ANSWER,[your response]\\n\\n"
                "CRITICAL: Extract the exact product name the user mentions. Keep the product name lowercase.\\n"
                "User sentence: " + conversationalInput;

    // Clean out quotation marks so we don't break the JSON curl block formatting
    size_t pos = 0;
    while ((pos = prompt.find("\"", pos)) != string::npos) {
        prompt.replace(pos, 1, "\\\"");
        pos += 2;
    }

    // Write out the payload package for Gemini's API endpoint
    ofstream jsonFile("request.json");
    jsonFile << "{\n  \"contents\": [{\n    \"parts\": [{\"text\": \"" << prompt << "\"}]\n  }]\n}";
    jsonFile.close();

    // Native Ubuntu curl request executing secure network transmission to Google AI Studio
    string command = "curl -s -X POST \"https://generativelanguage.googleapis.com/v1beta/models/gemini-2.5-flash:generateContent?key=" + apiKey + "\" -H \"Content-Type: application/json\" -d @request.json > response.json";
    system(command.c_str());

    // Open and parse the response package
    ifstream file("response.json"); if (!file.is_open()) return;
    stringstream buffer; buffer << file.rdbuf(); string content = buffer.str(); file.close();

    string searchToken = "\"text\": \""; size_t startPos = content.find(searchToken);
    if (startPos == string::npos) { cout << "Communication fault. Try rephrasing." << endl; return; }
    startPos += searchToken.length(); size_t endPos = content.find("\"", startPos);
    string rawResult = content.substr(startPos, endPos - startPos);

    // Chop the structured CSV response string from Gemini into localized data parameters
    stringstream ss(rawResult); string type, f1, f2, f3, f4;
    getline(ss, type, ','); getline(ss, f1, ','); getline(ss, f2, ','); getline(ss, f3, ','); getline(ss, f4, ',');
    if(!f1.empty() && f1[0] == ' ') f1.erase(0, 1); if(!f2.empty() && f2[0] == ' ') f2.erase(0, 1);
    if(!f3.empty() && f3[0] == ' ') f3.erase(0, 1); if(!f4.empty() && f4[0] == ' ') f4.erase(0, 1);

    if (type == "UPDATE") {
        if(f1.empty() || f2.empty()) return;
        
        int change = stoi(f2);
        inventoryTable[f1].available += change;
        if (change < 0) {
            inventoryTable[f1].units_sold += abs(change);
        }
        cout << "Inventory updated." << endl;
        saveTableToDisk();
        
        // UPGRADE: Sync the entire 5-column dashboard to the cloud immediately!
        //syncFullTableToGoogleSheets(sheetsUrl);

        if (inventoryTable[f1].available < inventoryTable[f1].benchmark) {
            triggerLowStockSMS(f1, inventoryTable[f1].available);
        }
    } 
    else if (type == "NEW") {
        if(f1.empty() || f2.empty() || f3.empty() || f4.empty()) return;
        inventoryTable[f1] = {0, stoi(f2), stod(f3), stod(f4), 0,0.0};
        cout << "Inventory item [" << f1 << "] added to catalog." << endl;
        saveTableToDisk();
        
        // UPGRADE: Sync the cloud sheet so the new product row shows up instantly with its CP/SP prices!
       // syncFullTableToGoogleSheets(sheetsUrl);
    }
    else if (type == "ANSWER") {
        cout << f1 << endl; // Display conversational insights directly to user
    }
    else if (type == "WASTE") {
        if(f1.empty() || f2.empty()) return;
        int wasteQty = stoi(f2);
        
        // Check if item exists in inventory map matrix
        if (inventoryTable.find(f1) != inventoryTable.end()) {
            inventoryTable[f1].available -= wasteQty;
            double lossAmount = wasteQty * inventoryTable[f1].cost_price;
            
            cout << "[⚠️] WASTE RECORDED: " << wasteQty << " units of [" << f1 << "] written off." << endl;
            cout << "[💸] Direct Financial Loss: Rs." << lossAmount << " (Net profits updated dynamically)" << endl;
            saveTableToDisk();
        }
    }
        else if (type == "DELETE") {
        if(f1.empty()) return;
        
        // Trim any trailing spaces or newlines from the product name
        if (!f1.empty() && f1.back() == '\n') f1.pop_back();
        if (!f1.empty() && f1.back() == '\r') f1.pop_back();

        // Check if the product actually exists in our map memory engine
        if (inventoryTable.find(f1) != inventoryTable.end()) {
            inventoryTable.erase(f1); // Completely purges the key-value pair
            cout << "[🗑️] SUCCESS: Product [" << f1 << "] has been permanently removed from the catalog." << endl;
            saveTableToDisk(); // Sync to local file storage instantly
        } else {
            cout << "[❌] ERROR: Product [" << f1 << "] could not be found in the database catalog." << endl;
        }
    }
    
    else if (type == "CUSTOM_SALE") {
        if(f1.empty() || f2.empty() || f3.empty()) return;
        int saleQty = stoi(f2);
        double customPrice = stod(f3);
        
        if (inventoryTable.find(f1) != inventoryTable.end()) {
            inventoryTable[f1].available -= saleQty;
            inventoryTable[f1].units_sold += saleQty;
            
            // Calculate Moving Average Selling Price: (Prior Total Revenue + New Batch Revenue) / Total Units Sold
            double newBatchRevenue = saleQty * customPrice;
            inventoryTable[f1].total_revenue += newBatchRevenue;
            inventoryTable[f1].selling_price = inventoryTable[f1].total_revenue / inventoryTable[f1].units_sold;
            
            cout << "[💰] CUSTOM BATCH SALE: " << saleQty << " units of [" << f1 << "] sold at Rs." << customPrice << " each." << endl;
            cout << "[📊] Dynamic Moving Average SP updated to: Rs." << inventoryTable[f1].selling_price << endl;
            saveTableToDisk();
            
            // Trigger your live Twilio cellular network buzzer if thresholds collapse
            if (inventoryTable[f1].available < inventoryTable[f1].benchmark) {
                triggerLowStockSMS(f1, inventoryTable[f1].available);
            }
        }
    }
}

int main() {
    // =========================================================================
    // !!! PASTE YOUR MASTER PRODUCTION CONFIGURATION DATA HERE !!!
    // =========================================================================
    string my_api_key = "PASTE YOUR GOOGLE GEMINI API";
    string my_sheets_url ="";
    // =========================================================================

    if (my_api_key == "") {
        cout << "[-] Configuration missing! Open main.cpp and configure your API Keys." << endl;
        return -1;
    }

    loadTableFromDisk();
    

    system("clear");
    cout << "========================================================" << endl;
    cout << "         SHEETKEEPER AI OMNICHANNEL REVOLUTION          " << endl;
    cout << "========================================================" << endl;
    cout << "Commands: Chat naturally, type 'view finance', or 'exit'" << endl;

    while (true) {
        // Poll for cloud updates left by the shopkeeper's phone before checking terminal input
        checkCloudUpdatesFromPhone(my_sheets_url, my_api_key);

        cout << "> ";
        string userInput;
        getline(cin, userInput);

        if (userInput == "exit") break;
        if (userInput.empty()) continue;
        

        // Manual reset switch
        if (userInput == "clear" || userInput == "clear all the data") {
            inventoryTable.clear();
            saveTableToDisk();
            
           
            
            cout << "Database completely cleared! " << endl;
            continue;
        }

        if (userInput == "view finance") {
            generateFinancialReport();
        } else {
            sendToGemini(userInput, my_api_key, my_sheets_url);
        }
    }

    return 0;
}