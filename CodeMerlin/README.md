CodeMerlin is a Python-based desktop application designed to provide automated, high-fidelity code reviews and performance optimizations. By leveraging locally-hosted Large Language Models (LLMs) via an OpenAI-compatible API, CodeMerlin analyzes source code for logical flaws, syntax errors, and algorithmic complexity (Big-O).

Technical Stack

    Language: Python 3.x

    Frontend: customtkinter (Modernized Tkinter wrapper)

    Concurrency: threading (Daemonized threads for non-blocking I/O)

    AI Integration: openai Python library (configured for localhost inference)

    Prompt Engineering: Custom system-level instruction set for structural and logic-based auditing.

Key Features

    Multi-Language Support: File I/O capabilities for .java, .py, .cpp, .js, and more.

    Real-time Streaming: Implements API response streaming for immediate feedback.

    Big-O Optimization: Specifically tuned to detect inefficient loops and suggest mathematically superior alternatives.

    Secure & Local: Designed to run entirely on a local machine (e.g., LM Studio) to ensure proprietary data privacy.

System Architecture

CodeMerlin acts as a middleware between the user and a local inference server:

    Ingestion: User loads source code via a native file explorer or manual paste.

    Request Layer: The application packages the code into a JSON payload with a specific "system persona" that prioritizes structural flaws.

    Inference: The payload is sent to a local server at http://localhost:1234.

    Streaming UI: The response is decoded and injected into a read-only text area to prevent accidental modification during review.

How to Run

    Initialize Local Server: Ensure your local LLM server is running at http://localhost:1234.

    Install Dependencies: pip install customtkinter openai

    Execute: python codemerlin.py
