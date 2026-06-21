# 🛒 SheetKeeper Assistant
A Linux terminal based  intelligent, C++ backend inventory engine powered by the Gemini API for natural language understanding and Twilio API for real-time cellular threshold notifications.

---

##  Core Features
* **Natural Language Parsing:** Process everyday retail phrases (e.g., "sold 5 cokes", "add 10 bread loaves") via Gemini flash extraction.
* **Automated Ledgers:** In-memory tracking with full disk state persistence (`database.txt`).
* **Cellular Alerts:** Real-time Twilio SMS generation when inventory levels fall below benchmarks.
---
## Significance 
This is a ter

---

## 🛠️ Local Setup & Execution Guide

Follow these steps to build and run the application on your local Linux / Ubuntu environment.

### 1. Install Prerequisites
Ensure you have a C++ compiler and the required SSL/networking dependencies installed:
```bash
sudo apt update
sudo apt install build-essential libcurl4-openssl-dev libssl-dev
