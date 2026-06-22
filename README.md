# 🛒 ShopKeeper Assistant
A Linux terminal based  intelligent, C++ backend inventory engine powered by the Gemini API for natural language understanding and Twilio API for real-time cellular threshold notifications.
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





### 1. Install Prerequisites
Ensure you have a C++ compiler and the required SSL/networking dependencies installed:
```bash
sudo apt update
sudo apt install build-essential libcurl4-openssl-dev libssl-dev
