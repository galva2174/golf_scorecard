## Overview
This C program simulates a golf scorecard management system, allowing players to input their golf scores, view statistics, and track their improvement over time. The program supports customizing golf courses with different numbers of holes, and it can calculate the player's average score, improvement trend, and handicap.

## Features
Custom Golf Courses: Allows you to define a custom golf course by specifying the number of holes, par for each hole, and the distance of each hole.  
Player and Course Details: Collects player information (name, handicap, total rounds played, total score) and stores golf course details.  
Rounds and Scores: Supports adding multiple rounds of scores for the player, keeping track of scores for each hole.  
Statistics Calculation:  
  Average score over multiple rounds.  
  Handicap calculation based on player's scores.  
  Improvement trend to track how the player has improved between rounds.  
Score Customization: Ability to apply a scoring factor to adjust scores based on different golf course formats.  
## File Structure  
Player Structure: Holds the player's name, handicap, total rounds played, and total score.  
GolfCourse Structure: Holds the course name, location, and details for each hole.  
Round Structure: Holds the scores for each round of play.  
Score Structure: Linked list structure that stores individual scores for holes within a round.  
Scorecard Structure: Combines the player, course, and rounds of play for calculating statistics and managing player performance.  
## Functions  
calculate_average_score: Computes the player's average score across all rounds.  
calculate_handicap: Calculates the player's handicap based on their current scores.  
calculate_improvement_trend: Tracks the player's improvement across multiple rounds.  
customize_score_format: Allows you to adjust the scores based on a customizable factor to handle different scoring preferences.  
add_custom_course: Input the details of a custom course, including the number of holes, par, and distance for each hole.  
create_score_node: Creates a new node for storing a score in the linked list.  
create_round_node: Creates a new node to store a round's scores in the linked list.  
add_score_to_round: Adds a new score to a round.  
add_round_to_scorecard: Adds a round to the scorecard.  
display_player_statistics: Displays the player's basic statistics, including name, total rounds played, and total score.  
display_hole_information: Displays the par and distance information for each hole in the course.  
