import 'package:flutter/material.dart';
import 'dart:math';


void main() {
  runApp(const TabBarDemo());
}

class Player {
  final int rating;
  final String name;
  final String team;
  final int jerseyNumber;

  Player(this.rating, this.name, this.team, this.jerseyNumber);

  @override
  String toString() {
    return '$name | Team: $team | Rating: $rating | Jersey: $jerseyNumber';
  }

  String toJerseyString() {
    return 'Jersey: $jerseyNumber | Example Player: $name, $team';
  }
}




List<Player> parsePlayers(String fileContent) {
  List<Player> players = [];

  List<String> lines = fileContent.split('\n');

  for (String line in lines) {
    if (line.trim().isEmpty) continue;

    List<String> parts = line.trim().split(' ');

    if (parts.length >= 5) {
      int rating = int.tryParse(parts[0]) ?? 0;
      String name = '${parts[1]} ${parts[2]}';
      String team = parts[3];
      int jersey = int.tryParse(parts[4]) ?? 0;

      players.add(Player(rating, name, team, jersey));
    }
  }

  return players;
}


class TabBarDemo extends StatefulWidget {
  const TabBarDemo({Key? key}) : super(key: key);

  @override
  _TabBarDemoState createState() => _TabBarDemoState();
}

class _TabBarDemoState extends State<TabBarDemo> {
  int rating = 0;
  int jersey = 0;
  int player = 0;
  List<Player> playerList = [];
  String currentPlayer = "Press Button To Randomize";
  String currentJersey = "Press Button To Randomize";

  double minRating = 65;
  double maxRating = 99;

  @override
  void initState() {
    super.initState();
    loadPlayerData();
  }

  Future<void> loadPlayerData() async {
    String data = await DefaultAssetBundle.of(context).loadString('assets/NbaRoster.txt');
    setState(() {
      playerList = parsePlayers(data);
    });
  }

  void randomizeJersey() {
    if(playerList.isNotEmpty) {
      setState(() {
        final randomIndex = Random().nextInt(playerList.length);
        final selectedJersey = playerList[randomIndex];
        currentJersey = selectedJersey.toJerseyString();
      });
    } else {
      setState(() {
        currentJersey = "No jerseys loaded, check your Roster.txt files!";
      });
    }
  }

  void randomizePlayer() {
    if(playerList.isNotEmpty) {
      setState(() {
        final randomIndex = Random().nextInt(playerList.length);
        final selectedPlayer = playerList[randomIndex];
        currentPlayer = selectedPlayer.toString();
      });
    } else {
      setState(() {
        currentPlayer = "No players loaded, check your Roster.txt file!";
      });
    }
  }

  void randomizeRating() {
    setState(() {
      rating = minRating.toInt() + Random().nextInt(maxRating.toInt() - minRating.toInt() + 1);
    });
  }

  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      home: DefaultTabController(
        length: 3,
        child: Scaffold(
          appBar: AppBar(
            foregroundColor: Colors.white,
            bottom: const TabBar(
              indicatorColor: Colors.white,
              unselectedLabelColor: Colors.white,
              labelColor: Colors.grey,
              tabs: [
                Tab(icon: Icon(Icons.sports_kabaddi), text: "Player"),
                Tab(icon: Icon(Icons.looks_4), text: "Rating"),
                Tab(icon: Icon(Icons.man), text: "Jersey"),
              ],
            ),
            title: const Text('2K21 Randomizer'),
            backgroundColor: Colors.blueGrey,
          ),
          body: Container(
            decoration: BoxDecoration(
              image: DecorationImage(
                image: AssetImage("assets/images/wallpaper.jpg"), // Background Image
                fit: BoxFit.cover, // Covers full screen
              ),
            ),
            child: TabBarView(
              children: [
                // Player Tab
                Center(
                  child: Column(
                    mainAxisSize: MainAxisSize.min,
                    children: [
                      Text(currentPlayer, style: TextStyle(fontSize: 24, color: Colors.white)),
                      SizedBox(height: 10),
                      ElevatedButton(
                        onPressed: randomizePlayer,
                        child: Text('Random Player'),
                      ),
                    ],
                  ),
                ),
                // Rating Tab
                Padding(
                  padding: const EdgeInsets.all(20.0),
                  child: Column(
                    mainAxisSize: MainAxisSize.min,
                    children: [
                      Text("Rating: $rating", style: TextStyle(fontSize: 24, color: Colors.white)),
                      SizedBox(height: 20),

                      // Min Rating Slider
                      Text("Min Rating: ${minRating.toInt()}", style: TextStyle(color: Colors.white)),
                      SizedBox(
                        width: 250,
                        child: Slider(
                          value: minRating,
                          min: 0,
                          max: maxRating,
                          divisions: maxRating.toInt(),
                          label: minRating.toInt().toString(),
                          onChanged: (value) {
                            setState(() {
                              minRating = value;
                              if (minRating > maxRating) minRating = maxRating;
                            });
                          },
                        ),
                      ),
                      // Max Rating Slider
                      Text("Max Rating: ${maxRating.toInt()}", style: TextStyle(color: Colors.white)),
                      SizedBox(
                        width: 250,
                        child: Slider(
                          value: maxRating,
                          min: minRating,
                          max: 99,
                          divisions: 99 - minRating.toInt(),
                          label: maxRating.toInt().toString(),
                          onChanged: (value) {
                            setState(() {
                              maxRating = value;
                              if (maxRating < minRating) maxRating = minRating;
                            });
                          },
                        ),
                      ),

                      SizedBox(height: 20),
                      ElevatedButton(
                        onPressed: randomizeRating,
                        child: Text('Random Rating'),
                      ),
                    ],
                  ),
                ),
                // Jersey Tab
                Center(
                  child: Column(
                    mainAxisSize: MainAxisSize.min,
                    children: [
                      Text(currentJersey, style: TextStyle(fontSize: 24, color: Colors.white)),
                      SizedBox(height: 10),
                      ElevatedButton(
                        onPressed: randomizeJersey,
                        child: Text('Random Jersey'),
                      ),
                    ],
                  ),
                ),
              ],
            ),
          ),
        ),
      ),
    );
  }
}
