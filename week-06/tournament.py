# Simulate a sports tournament

import csv
import sys
import random

# Number of simluations to run
N = 95000


def main():

    # Ensure correct usage
    if len(sys.argv) != 2:
        sys.exit("Usage: python tournament.py FILENAME")

    teams = []
    # TODO: Read teams into memory from file
    # Open file name provided as cli argument
    with open(sys.argv[1]) as file:
        # Create csv reader object
        reader = csv.DictReader(file)
        # In each row convert rating to number and append whole row to the teams variable
        for row in reader:
            row["rating"] = int(row["rating"])
            teams.append(row)

    counts = {}
    # TODO: Simulate N tournaments and keep track of win counts
    # For each simulation instance in N check winner with simulate_tournament and append to counts
    for instance in range(0, N):
        winner = simulate_tournament(teams)
        # If team is already added, increment by one
        if winner in counts:
            counts[winner] += 1
        # If not, append it with value 1
        else:
            counts[winner] = 1

    # Print each team's chances of winning, according to simulation
    for team in sorted(counts, key=lambda team: counts[team], reverse=True):
        print(f"{team}: {counts[team] * 100 / N:.1f}% chance of winning")


def simulate_game(team1, team2):
    """Simulate a game. Return True if team1 wins, False otherwise."""
    rating1 = team1["rating"]
    rating2 = team2["rating"]
    probability = 1 / (1 + 10 ** ((rating2 - rating1) / 600))
    return random.random() < probability


def simulate_round(teams):
    """Simulate a round. Return a list of winning teams."""
    winners = []

    # Simulate games for all pairs of teams
    for i in range(0, len(teams), 2):
        if simulate_game(teams[i], teams[i + 1]):
            winners.append(teams[i])
        else:
            winners.append(teams[i + 1])

    return winners


def simulate_tournament(teams):
    """Simulate a tournament. Return name of winning team."""
    # TODO
    # While teams has more than one entry, loop over it and execute simulate_round
    # Assing simulate_round result back to teams on each run
    # When done, return remaining entry team name
    while len(teams) > 1:
        teams = simulate_round(teams)

    return teams[0]['team']


if __name__ == "__main__":
    main()


""" 
CONTENTS OF ANSWERS.TXT

Times:

10 simulations: 0m0.029s
100 simulations: 0m0.033s
1000 simulations: 0m0.040s
10000 simulations: 0m0.125s
100000 simulations: 0m0.924s
1000000 simulations: 0m8.084s

Questions:

Which predictions, if any, proved incorrect as you increased the number of simulations?:

In "N less than 100" simulations, middle ranked countires (Canada, Sweeden, Norway, Netherlands etc.) were getting large percentages and bottom ranked countries were not showing at all.
At N 1000 predictions stabilized enough to have presentable results.


Suppose you're charged a fee for each second of compute time your program uses.
After how many simulations would you call the predictions "good enough"?:

Since in most cases N of 1000 gets processed under half a second with similar probability ranks to 10000 which mostly gets over one second or running time, that would be a "two instances per fee payed" and viable option.

"""