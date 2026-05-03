# 📍 Campus WiFi Navigator

A smart pathfinding tool that helps you find the shortest route between buildings on campus using Dijkstra’s algorithm. No more wandering around trying to find the ECE building!

### ✨ Features
- *Interactive building selection* — Choose from 11 mapped campus locations
- *Shortest path with Dijkstra’s* — Efficient pathfinding using an adjacency matrix
- *Clean console output* — Displays the route and total distance
- *No direct path handling* — Returns `999` when two buildings aren’t connected

### 🏫 Campus Building Codes
Code | Building | Code | Building
2 | Diploma Building | 3 | Pavilion
4 | RIHC | 5 | Library
6 | Buddha Garden | 7 | Mechanical Bldg
8 | ECE Building | 9 | CSE Building
10 | EE Building | 11 | Back Gate


> `999` = No direct path exists between the two buildings

### 🚀 How to Compile & Run
1. *Clone the repository*
   git clone https://github.com/apsanap06/Campus_WiFi_Navigator.git

2. *Navigate to the project folder*
   cd Campus_WiFi_Navigator

3. *Compile the C program*
   gcc main.c -o campus_nav

4. *Run the executable*
   ./campus_nav


### 🛠️ Tech Stack
- *Language*: C  
- *Algorithm*: Dijkstra’s Shortest Path Algorithm  
- *Data Structure*: Adjacency Matrix

### 📸 Sample Output
Enter source building code: 0
Enter destination building code: 7
Shortest Path: 2 -> 6 -> 7  
Total Distance: 340
<img width="694" height="613" alt="image" src="https://github.com/user-attachments/assets/cba82afe-02f7-4f4e-999e-fed4e36ebbd7" />

