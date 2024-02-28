import csv
import requests


def main():
    # Read NYTimes Covid Database
    download = requests.get(
        "https://raw.githubusercontent.com/nytimes/covid-19-data/master/us-states.csv"
    )
    decoded_content = download.content.decode("utf-8")
    file = decoded_content.splitlines()
    reader = csv.DictReader(file)

    # Construct 14 day lists of new cases for each states
    new_cases = calculate(reader)
    #print(new_cases)
    # Create a list to store selected states
    states = []
    print("Choose one or more states to view average COVID cases.")
    print("Press enter when done.\n")

    while True:
        state = input("State: ")
        if state in new_cases:
            states.append(state)
        if len(state) == 0:
            break

    print(f"\nSeven-Day Averages")


    # Print out 7-day averages for this week vs last week
    comparative_averages(new_cases, states)


# TODO: Create a dictionary to store 14 most recent days of new cases by state
def calculate(reader):
    new_cases = dict()
    for row in reader:
        state = row['state']
        cases = int(row['cases'])
        if state not in new_cases.keys():
            new_cases[state]=list()
            new_cases[state].append(cases)
        elif len(new_cases[state]) < 14:
            new_cases[state].append(cases)
        else:
            new_cases[state].append(cases)
            del new_cases[state][0]
       # print(row['state'], row['cases'])
    return new_cases


# TODO: Calculate and print out seven day average for given state
def comparative_averages(new_cases, states):
    for state in states:
        old_avg = int(sum(new_cases[state][0:7])/7)
        avg = int(sum(new_cases[state][7:])/7)
        try:
            dec = int((1 - avg/old_avg)*100)
        except ZeroDivisionError:
            dec = 0
        print(f"{state} had a 7-day average of {avg} and a decrease of {dec}%.")



main()
