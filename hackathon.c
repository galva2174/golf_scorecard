#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int num_holes;
struct Hole 
{
    int number;
    int par;
    int distance;
};
struct GolfCourse 
{
    char name[50];
    char location[50];
    struct Hole *holes; 
};
struct Player 
{
    char name[50];
    float handicap;
    int total_rounds_played;
    int total_score;
    
};
struct Score 
{
    int score;
    struct Score *next;
};
struct Round 
{
    struct Score *scores;
    struct Round *next;
};
struct Scorecard 
{
    struct Player player;
    struct GolfCourse course;
    struct Round *rounds;
};
float calculate_average_score(struct Round *rounds) 
{
    float sum = 0.0;
    int count = 0;
    struct Round *currentRound = rounds;
    while (currentRound != NULL) 
    {
        struct Score *currentScore = currentRound->scores;
        while (currentScore != NULL) 
        {
            sum += currentScore->score;
            count++;
            currentScore = currentScore->next;
        }
        currentRound = currentRound->next;
    }

    return count > 0 ? sum / count : 0.0;
}
float calculate_handicap(struct Player player, struct Round *rounds) 
{
    float sum_of_differentials = 0.0;
    int count = 0;

    struct Round *currentRound = rounds;
    while (currentRound != NULL) 
    {
        struct Score *currentScore = currentRound->scores;
        if (currentScore != NULL) 
        {
            float differential = (float)(currentScore->score) - player.handicap;
            sum_of_differentials += differential;
            count++;
        }
        currentRound = currentRound->next;
    }

    return count > 0 ? sum_of_differentials / count : 0.0;
}

float calculate_improvement_trend(struct Round *rounds) 
{
    float sum_of_improvements = 0.0;
    int count = 0;

    struct Round *currentRound = rounds;
    while (currentRound != NULL && currentRound->next != NULL) 
    {
        struct Score *currentScore = currentRound->scores;
        struct Score *nextScore = currentRound->next->scores;

        if (currentScore != NULL && nextScore != NULL) 
        {
            float improvement = (float)(currentScore->score) - nextScore->score;
            sum_of_improvements += improvement;
            count++;
        }

        currentRound = currentRound->next;
    }

    return count > 0 ? sum_of_improvements / count : 0.0;
}
void customize_score_format(struct Player *player, struct Round *rounds) //to handle different golf courses and formats and scoring preferences
{
    float factor;
    printf("Enter scoring factor: ");
    scanf("%f", &factor);

    struct Round *currentRound = rounds;
    while (currentRound != NULL) 
    {
        struct Score *currentScore = currentRound->scores;
        while (currentScore != NULL) 
        {
            currentScore->score = (int)(currentScore->score * factor);
            currentScore = currentScore->next;
        }
        currentRound = currentRound->next;
    }
}
void add_custom_course(struct Player *player, struct GolfCourse *course) 
{
    printf("Enter course name: ");
    scanf("%s", course->name);

    printf("Enter course location: ");
    scanf("%s", course->location);
    printf("Enter the number of holes: ");
    scanf("%d", &num_holes);
    course->holes = (struct Hole *)malloc(num_holes * sizeof(struct Hole));
    printf("Enter details for each hole:\n");
    for (int i = 0; i < num_holes; i++) 
    {
        printf("Hole %d - Par: ", i + 1);
        scanf("%d", &course->holes[i].par);

        printf("Hole %d - Distance: ", i + 1);
        scanf("%d", &course->holes[i].distance);
    }
}
struct Score *create_score_node(int score) 
{
    struct Score *newScore = (struct Score *)malloc(sizeof(struct Score));
    newScore->score = score;
    newScore->next = NULL;
    return newScore;
}
struct Round *create_round_node() 
{
    struct Round *newRound = (struct Round *)malloc(sizeof(struct Round));
    newRound->scores = NULL;
    newRound->next = NULL;
    return newRound;
}
void add_score_to_round(struct Round *round, int score) 
{
    struct Score *newScore = create_score_node(score);
    if (round->scores == NULL) 
    {
        round->scores = newScore;
    }
    else 
    {
        struct Score *currentScore = round->scores;
        while (currentScore->next != NULL) 
        {   
            currentScore = currentScore->next;
        }
        currentScore->next = newScore;
    }
}
void add_round_to_scorecard(struct Scorecard *scorecard, struct Round *round) 
{
    struct Round *currentRound = scorecard->rounds;
    if (currentRound == NULL) 
    {
        scorecard->rounds = round;
    } 
    else 
    {
        while (currentRound->next != NULL) 
        {
            currentRound = currentRound->next;
        }
        currentRound->next = round;
    }
}

void display_player_statistics(struct Player player) 
{
    printf("Player Statistics:\n");
    printf("Name: %s\n", player.name);
    printf("Handicap: %.2f\n", player.handicap);
    printf("Total Rounds Played: %d\n", player.total_rounds_played);
    printf("Total Score: %d\n", player.total_score);
}

void display_hole_information(struct GolfCourse course) 
{
    printf("Hole Information for Course %s:\n", course.name);
    for (int i = 0; i < num_holes; i++) 
    {
        printf("Hole %d - Par: %d, Distance: %d\n", i + 1, course.holes[i].par, course.holes[i].distance);
    }
}
int main() 
{
    struct Player player1;
    printf("Enter player name: ");
    scanf("%s", player1.name);

    printf("Enter player handicap: ");
    scanf("%f", &player1.handicap);

    printf("Enter total rounds played: ");
    scanf("%d", &player1.total_rounds_played);

    printf("Enter total points scored(initially): ");
    scanf("%d", &player1.total_score);
    struct GolfCourse custom_course;
    add_custom_course(&player1, &custom_course);
    display_hole_information(custom_course);
    struct GolfCourse course1;
    struct Scorecard scorecard1 = {player1, course1, NULL};

    for (int round_num = 1; round_num <= player1.total_rounds_played; round_num++) {
        struct Round *round = create_round_node();

        printf("Enter scores for Round %d:\n", round_num);
        for(int hole_num = 1; hole_num <= num_holes; hole_num++) {
            int score;
            printf("Enter score for Hole %d: ", hole_num);
            scanf("%d", &score);
            add_score_to_round(round, score);
        }

        add_round_to_scorecard(&scorecard1, round);
    }  

    display_player_statistics(player1);

    float average_score = calculate_average_score(scorecard1.rounds);
    printf("Average Score: %.2f\n", average_score);

    customize_score_format(&player1, scorecard1.rounds);
  
    float handicap = calculate_handicap(player1, scorecard1.rounds);
    printf("Handicap: %.2f\n", handicap);

    float improvement_trend = calculate_improvement_trend(scorecard1.rounds);
    printf("Improvement Trend: %.2f\n", improvement_trend);

    free(custom_course.holes);
  
    return 0;
}
