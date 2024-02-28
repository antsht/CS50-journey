import csv
import sys


def main():
    # Ensure correct usage
    if len(sys.argv) != 3:
        sys.exit("Usage: python dna.py DBFilemame SequencesFilname")

    # TODO: Read database file into a variable
    dnaDB = []
    with open(sys.argv[1]) as file:
        reader = csv.DictReader(file)
        for record in reader:
            dnaDB.append(record)
    dnaKeys = list(dnaDB[0].keys())[1:]
    # print(dnaDB)
    # print(list(dnaDB[0].keys())[1:])
    # TODO: Read DNA sequence file into a variable
    with open(sys.argv[2]) as file:
        DNAtoCheck = file.readline()
    # print(DNAtoCheck)
    # TODO: Find longest match of each STR in DNA sequence
    matches = {}
    for key in dnaKeys:
        matches[key] = longest_match(DNAtoCheck, key)
    # print(matches)
    # TODO: Check database for matching profiles
    for record in dnaDB:
        match = True
        for STR in dnaKeys:
            # print(f"STR: {STR} RecordSTR: {record[STR]} matches: {matches[STR]}")
            if int(record[STR]) != int(matches[STR]):
                match = False
        if match:
            print(record["name"])
            sys.exit(0)
    print("No match")
    return


def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""

    # Initialize variables
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):
        # Initialize count of consecutive runs
        count = 0

        # Check for a subsequence match in a "substring" (a subset of characters) within sequence
        # If a match, move substring to next potential match in sequence
        # Continue moving substring and checking for matches until out of consecutive matches
        while True:
            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1

            # If there is no match in the substring
            else:
                break

        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    # After checking for runs at each character in seqeuence, return longest run found
    return longest_run


main()
