# randomizer2k21

A Randomizer for 2k21 I made during my free time freshman year at ISU

Technical Stack

    Language: Dart

    Framework: Flutter (Material Design)

    Data Management: Object-Oriented Player modeling and internal list-mapping

    Concurrency: Async/Await for asset retrieval

  Key Features

    Dynamic Player Selection: Randomly selects from a parsed roster list to provide full player profiles, including team and rating data.

    Parameterized Rating Generator: Uses a bounded random number generator (Rating=min+Random(max−min)) to simulate performance stats within user-specified limits.

    High-Performance Text Parsing: Efficiently splits and cleans multi-line string data to ensure data integrity even with irregular input files.

    Global State Management: Updates the application view in real-time using 'setState', ensuring a smooth and reactive user experience.


  How to Build & Run

    Environment Setup: Ensure the Flutter SDK is installed and configured.

    Asset Configuration: Place the 'NbaRoster.txt' and 'wallpaper.jpg' files in the designated 'assets' directory.

    Dependency Installation:
    flutter pub get

    Execution:
    flutter run
