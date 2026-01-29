# 🏠 Real Estate Management System (REMS)
<img width="1195" height="2026" alt="_C__Users_HP_OneDrive_Desktop_hehe html (3)" src="https://github.com/user-attachments/assets/c54f4089-2de1-4353-a675-8fe7633c8d6c" />

> **A persistent, role-based digital marketplace engine built from scratch in C++.**

![Language](https://img.shields.io/badge/C%2B%2B-17-00599C?style=for-the-badge&logo=c%2B%2B)
![Platform](https://img.shields.io/badge/Windows-Console-0078D6?style=for-the-badge&logo=windows)
![Architecture](https://img.shields.io/badge/Architecture-Parallel_Arrays-FF5722?style=for-the-badge)
![Status](https://img.shields.io/badge/Status-Completed-success?style=for-the-badge)

## 💡 The Problem & The Solution

**The Problem:** Most beginner C++ console projects suffer from "amnesia"—they lose all data the moment the program terminates.
**The Solution:** REMS.

REMS is a full-stack simulation of a real estate marketplace that implements a **custom Database Engine** using raw file handling. It features a secure "Gatekeeper" login system, automated financial logic, and strict data isolation—all without relying on SQL or external libraries.

---

## 🏗️ System Architecture

I designed this system with a strict focus on **Data Security** and **Role Isolation**.
* **Sellers** operate in a sandbox where they can only modify their own listings.
* **Buyers** have read-only access to the market but write-access to their own transaction logs.
* **Admins** oversee the entire flow via a master control panel.

![System Architecture]
<img width="1521" height="1334" alt="_C__Users_HP_OneDrive_Desktop_hehe html (5)" src="https://github.com/user-attachments/assets/95f442f7-5623-4a14-8233-f04d1782d1cb" />

*(Note: This flowchart represents the Role-Based Access Control logic implemented in the source code.)*

---

## 🚀 Key Features

### 🔐 1. "Gatekeeper" Security Protocol
Unlike standard apps where anyone can join, REMS mimics enterprise security:
* **Pending Queue:** New signups are assigned `Status: 0` (Pending).
* **Admin Verification:** Users cannot log in until an Administrator reviews and approves their request.
* **Scam Prevention:** Integrated **Reputation System** allows buyers to view a seller's rating history before transferring funds.

### 💾 2. Custom Persistence Layer
I engineered a file-handling system using `<fstream>` that functions as a lightweight database:
* **Real-Time Sync:** Transactions are written to `properties.txt` and `users.txt` instantly.
* **Data Parsing:** Custom algorithms parse CSV (Comma Separated Values) strings into parallel arrays for processing.

### ⏳ 3. Temporal Business Logic
The system understands time using the C++ `<ctime>` library:
* **Rent Automation:** Automatically calculates the days elapsed since a rental contract started.
* **Overdue Flags:** If `(Current Date - Due Date) > 30`, the tenant is flagged as **OVERDUE**.

### 🔄 4. Ownership Transfer Cycle
The system handles complex state changes:
1.  **Listing:** Seller posts property (Visible in Market).
2.  **Sale:** Buyer purchases property -> Status updates to "Sold" -> Revenue logged.
3.  **Unregister:** If the Buyer later sells the property offline, they can "Unregister" ownership to remove it from their portfolio.

---

## 🛠️ Technical Stack

| Component | Implementation | Why? |
| :--- | :--- | :--- |
| **Core Logic** | C++ (Procedural) | To master memory management and logic building basics. |
| **Database** | Custom File I/O (`fstream`) | To understand how data persistence works at a low level. |
| **Data Structure** | Synchronized Parallel Arrays | Efficient data linking via primary index keys (`idx`). |
| **Algorithms** | Bubble Sort & Linear Search | For "Filter by Price/Size" and "Search by ID" features. |
| **UI** | Windows API (`<windows.h>`) | Custom color themes and console cursor positioning. |

---

## 👨‍💻 User Roles

### 🔴 Administrator (The Superuser)
* **User Management:** Approve/Reject signups, Ban users.
* **Audit:** View total platform revenue and transaction logs.
* **Clean Up:** Delete illegal or duplicate listings.

### 🔵 Seller (The Vendor)
* **Asset Control:** Add, Edit, or Delete property listings.
* **Privacy:** Can **only** access data linked to their specific Username.
* **Lifecycle:** Mark items as "Sold" or "Unlist" them to prevent resale.
* **Inbox:** Read enquiries from potential buyers.

### 🟢 Buyer (The Customer)
* **Discovery:** Search market by ID, City, or Price range.
* **Transactions:** Rent properties or buy assets outright.
* **Safety:** Report scams and rate seller interactions.
* **Portfolio:** Manage purchased properties and unregister them if sold.

---

## ⚙️ Installation & Usage

### Prerequisites
* A C++ Compiler (GCC/MinGW) or an IDE (Visual Studio, Dev-C++, VS Code).
* **Operating System:** Windows (Required for `<windows.h>` UI components).

### Steps
1.  **Clone the Repo:**
    ```bash
    git clone [https://github.com/YourUsername/REMS-CPP.git](https://github.com/YourUsername/REMS-CPP.git)
    ```
2.  **Compile:**
    Open `main.cpp` and compile using C++11 standard.
3.  **Run:**
    Execute the `.exe` file.
    > **Note:** The repository includes `users.txt` and `properties.txt` with dummy data so you can test the system immediately without signing up.

---

## 🔮 Future Roadmap

This project lays the foundation for a scalable enterprise system.
- [ ] **OOP Migration:** Encapsulate logic into `User`, `Property`, and `Transaction` classes.
- [ ] **Hashing:** Implement SHA-256 for password encryption.
- [ ] **GUI:** Port the logic to Qt or .NET MAUI for a graphical interface.

---

## 🏆 Credits

**Developer:**
* **Muhammad Umer Fareed** - *Full Stack Logic, Architecture & UI*

**Supervisor:**
* **Dr. Maida Shahid & Mr. Kamran Mustafa** - *For guidance on system architecture and logic flow.*

---

<p align="center">
  <i>Built with ❤️ in C++ | Programming Fundamentals Semester Project</i>
</p>
