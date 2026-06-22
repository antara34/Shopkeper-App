# 🛒 ShopKeeper Assistant

### Project Introduction

An intelligent, Linux terminal-based inventory engine powered by a C++ backend. It uses the Gemini API for natural language understanding and the Twilio API for sending real-time cellular low-stock notifications. 

This project is highly useful for shopkeepers because it allows them to update transactions using simple human commands and get instant business insights analyzed by Gemini. In turn, Gemini updates the system's database and sends back a response. 
By eliminating the usual manual updating of product stocks in spreadsheets, this engine makes a shopkeeper's job incredibly time-efficient and precise. 

### ✨ Key Features Built into the System:
* **Smart Command Parsing:** You don't need to type rigid code just give commands in human language  engine instantly understands the product, quantity, and intent. "sold 12 milk", "stock 30 maggi","bought 20 sweets","add biscuits with bm 5,cost 12,sp 15".
* **Existing Product Updates:** Shopkeepers can effortlessly update the benchmark (BM), cost price (CP), or selling price (SP) of any existing product in the catalog whenever they want, instantly locking the new configurations into memory.
* **Automated Net Profit Calculations:** The engine tracks your total costs and revenues to show you exactly how much profit your business is making.
* **Average Selling Price Updates:** If the same product is sold at different rates over time, the system automatically calculates and updates its average selling price."sold 8 coke for 20 rs"
* **Waste & Loss Tracking:** It keeps track of and updates your net amounts according to products that get wasted or damaged, alongside items that are successfully sold. "5 pepsi wasted".
* **Automated Low-Stock Text Alerts:** The second a product's stock drops below its safe boundary (Benchmark), the C++ backend automatically triggers a text message directly to your phone so you never run out of supply.
* **Organized Financial Table Display:** At any time, shopkeepers can generate a beautifully structured, clean table matrix that lists every product name alongside its benchmarks, current costs, prices, stock levels, and total units sold for clear visual tracking."view finance"
* **Easy Mistake-Deletion:** If a product is added by mistake or needs to be removed from the catalog completely, it can be instantly wiped from the memory system using a quick, straightforward delete command."delete pepsi"
* clear the whole database using "clear" command.
  
### Deep-Dive System Architecture

SheetKeeper Assistant is a high-performance console application that wraps a native C++ execution loop around cloud-hosted neural parsing architectures. It intercepts chaotic, variable human shop text (e.g., *"sold 12 milkshakes"*, *"add maggi with bm 5, cost 8 and sp 10"*) and forces the remote model to act as a deterministic, zero-latency database compiler. 

---

## 🏗️ Technical Deep-Dive: How It Works under the Hood

To make this application ultra-fast and resilient for a live store clerk environment, the system utilizes a custom network architecture broken into three distinct execution pillars:

```text
  [ Shopkeeper Input ] 
           │
           ▼
  [ C++ main() Loop ] ──(Keyword Match)──► [ Local Memory Override ] ──► [ Update Ledger/Matrix ]
           │                                                                     │
     (No Raw Match)                                                              ▼
           │                                                            [ printFinancialReport() ]
           ▼
  [ Strict Prompt Engineering ] 
           │
           ▼
  [ Native libcurl POST Request ] ──► [ Google Gemini Gateway ]
                                                │
                                                ▼
                                    [ Structured Response ]
                                     (e.g., "UPDATE,milk,5")
                                                │
                                                ▼
                                    [ C++ String Tokenizer ]
                                                │
                                                ▼
                                    [ State Mutation & Disk Commit ]
```

---
### 1.Forcing Gemini into a terminal state Parser
Standard LLM implementations return broad, conversational, and highly unpredictable text blocks. For a C++ compiled environment, unpredictable string shapes mean logic exceptions and system crashes.
This blueprint strips away the model's chatty behavior, forcing it to analyze incoming text against a rigid array of 7 state-changing database flags:

`UPDATE` (Inventory changes)

`NEW` (Catalog inclusion)

`DELETE` (Complete key erasure)

`WASTE` (Spoilage registration)

If the model detects a transaction, it is structurally barred from responding with human prose. It must return a strict comma-delimited array packet shape containing no spaces: `ACTION,PRODUCT_NAME,VARIABLE_VALUE`.
### 2. Low-Level Network Pipeline: Native libcurl POST Configuration
The application bypasses heavy, slow runtime environments and communicates directly over the sockets layer using libcurl.
Instead of performing a standard web-browser standard GET dump (which throws a 404 Gateway Error if loaded via consumer addresses), the application explicitly configures a structural data injection request payload over TLS/SSL:
```C++
// Explicit system level mapping layout inside the engine runtime
struct curl_slist* headers = NULL;
headers = curl_slist_append(headers, "Content-Type: application/json");

curl_easy_setopt(curl, CURLOPT_URL, "[https://generativelanguage.googleapis.com/v1beta/models/gemini-2.5-flash:generateContent?key=](https://generativelanguage.googleapis.com/v1beta/models/gemini-2.5-flash:generateContent?key=)...");
curl_easy_setopt(curl, CURLOPT_POSTFIELDS, jsonPayload.c_str());
curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
```
###  3. Microsecond-Latency Memory Matrices & In-Memory Ledgers
Once the system captures the parsed actions, it performs state updates across an optimized internal tracking layout:

*Lookup Speeds: Operates on an analytical C++ hash map matching unique alphanumeric item strings to structured transactional data schemas (`benchmark`, `cost_price`, `selling_price`, `available`, `units_sold`).

* Disk Auto-Recovery: Every data modification triggers a background stream-write to `database.txt`. If the local console environment terminates abruptly, booting the software re-reads the sequential file stream and instantly reconstructs the identical financial matrix state.
---
## 📊 Live System Interface Showcases
Here is the fully functional engine state operating natively on a Linux terminal sub-environment:

Real-Time Financial Ledger Generation
When users type view finance, the system renders an adaptive visual spreadsheet grid tracking operational expenditures, profit margins, and sales :

<img width="850" height="480" alt="Screenshot (139)" src="https://github.com/user-attachments/assets/5e69ce5f-1b63-492e-88f0-7f60a33f6f5e" />

<img width="850" height="480" alt="Screenshot (140)" src="https://github.com/user-attachments/assets/b4988d72-337c-4576-a889-49d5e4dbb7b1" />

Automated Cellular Alert Dispatches

The absolute second a transaction causes stock levels to fall below an item's specific benchmark parameter, the C++ thread intercepts the change, opens an auxiliary network hookup, and forwards an SMS warning layout right to the shop operator's smartphone:

<img width="250" height="480" alt="WhatsApp Image 2026-06-22 at 5 51 02 PM" src="https://github.com/user-attachments/assets/98425b85-1b8f-4fc4-a262-b3cb660e8086" />

##  How to Run & Verify Locally 

Follow these exact steps to clone, compile, and run the ShopKeeper Assistant engine natively inside your local Linux/Ubuntu terminal environment.

* Step 1: Clone the Architecture
Clone this repository to your local machine and navigate into the project root directory:
```bash
git clone https://github.com/antara34/Shopkeper-App.git
cd Shopkeper-App
```
* step 2 :The application uses native system libraries to communicate securely with the Gemini and Twilio APIs. Install the required packages:
```bash
sudo apt update
sudo apt install build-essential libcurl4-openssl-dev libssl-dev
```
* Step 3:  Insert Your API Keys Directly in main.cpp
Open main.cpp in VS Code or your preferred terminal text editor, search for the placeholder strings, and replace them with your actual active API credentials:
```C++
string account_sid = "PASTE TWILIO ACCOUNT SID";
string auth_token  = "TWILIO AUTHENTICATION NUMBER";
string twilio_num  = "TWILIO TRIAL NUMBER"; //Get you twilio trial number and  paste here
string my_real_num = "YOUR REAL NUMBER"; // Your personal number with country code

string my_api_key = "PASTE YOUR GOOGLE GEMINI API";// paste your google api
```
* Step 4: Compile and boot the engine
```bash
g++ main.cpp -o shopkeeper
./shopkeeper
```




