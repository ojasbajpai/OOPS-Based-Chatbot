# EdTech Support Multi-Persona Chatbot

A sophisticated, modular C++ chatbot system designed to handle multiple specialized AI personas. This project utilizes Object-Oriented Programming (OOP) principles, including Inheritance, Composition, and Dynamic Memory Management, to provide an extensible and persistent learning experience.

## Features
* **Multi-Persona Architecture:** Seamlessly switch between Support, Sales, and Technical AI personas.
* **Persistent Knowledge Base:** Each persona maintains its own `_memory.txt` file, allowing the system to "learn" and recall keywords even after restarting.
* **OOP Design Patterns:**
    * **Inheritance:** Specialization of chatbot types (`EdTechSupportBot`).
    * **Composition:** Modular live support integration (`LiveSupport` class).
    * **Manager Pattern:** Centralized `ChatbotManager` for handling state and persona switching.
* **Flexible Keyword Matching:** Intelligent search logic that detects keywords within complex user sentences.

## Project Structure
* `main.cpp`: The core engine containing the class hierarchies and the chatbot manager.
* `support_memory.txt`: Knowledge base for customer service queries.
* `sales_memory.txt`: Knowledge base for product pricing, courses, and discounts.
* `tech_memory.txt`: Knowledge base for technical troubleshooting and error codes.

## Getting Started

### Prerequisites
* A C++ compiler supporting C++17 (e.g., `g++` on macOS/Linux or MinGW on Windows).

### Compilation
Open your terminal in the project directory and run:

    g++ -std=c++17 main.cpp -o chatbot

## Usage
* **Launch:** Execute `./chatbot` in your terminal.
* **Interaction:** Type naturally. If the bot doesn't know a keyword, it will prompt you to teach it.
* **Switching Personas:** Type `change ai` at any time to switch to a different knowledge base.
* **Live Support:** Type `support` or `human` while using the Support persona to retrieve contact information.

## Predefined Knowledge
The system is pre-configured with several baseline responses:

| Persona | Key Topics Covered |
| :--- | :--- |
| **Support** | Refunds, Login issues, Certificate status, Password resets. |
| **Sales** | Course pricing, Bundle discounts (NEW20), Demo booking. |
| **Technical** | Browser cache, API documentation, Video playback, Crashes. |

## Learning Mechanism
When the chatbot encounters an unknown query, it triggers a learning sequence:
1. **Input:** User provides a new keyword and an associated response.
2. **Persistence:** The pair is appended to the relevant `.txt` file, ensuring the bot retains this knowledge permanently.

## Technical Documentation
* **Base Class (`Chatbot`):** Handles core file I/O, `std::unordered_map` storage, and string normalization.
* **Manager (`ChatbotManager`):** Manages an `aiPool` (vector of unique pointers) and state transitions between personas.
* **Composition:** `FinalChatbot` utilizes `LiveSupport` as a member object to inject support contact functionality without redundant code.
