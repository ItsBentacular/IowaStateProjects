My second big project at ISU as a freshman. Made using Java/JavaFX, it is me and a group of 3 others' attempt at blackjack using only Java and its addons.
While it is uncompiled, if compiled using maven and javaFX, it does function, and is a pretty good representation of blackjack. All of the art is Handmade using piskel pixel editor.
Credits to: Ethan Cyzon, Grayson Burton, and Robin Lin for working with me on this project.


Technical Stack

    Language: Java (JDK 17+)

    GUI Framework: JavaFX

    Build System: Maven

    Asset Creation: Handmade pixel art via Piskel (By me!)

    Key Java Concepts: Collections API (ArrayList, Shuffling), Switch Expressions, Exception Handling, and Resource Stream I/O.


  Key Features

    Dynamic Deck Management: A 52-card deck implementation with automated re-initialization and shuffling when resources are depleted.

    Automated Dealer AI: Implements standard Blackjack rules where the dealer must "hit" until reaching a score of 17, ensuring a consistent game loop.

    Error-Resilient GUI: The Card class features an internal "Placeholder" system; if a specific image asset is missing, the program dynamically generates a safe state rather   than throwing a NullPointerException.

    Financial Tracking System: Includes a "Money" class to handle betting logic, blackjack-specific payouts, and persistent bankroll management.

How to Build & Run
This project is managed by Maven. To build and run the application, ensure you have JavaFX configured in your environment:

    Clean and Install:
    mvn clean install

    Execute:
    mvn javafx:run
