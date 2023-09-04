import csv
import sys


def main():

    # TODO: Check for command-line usage
    if len(sys.argv) != 3:
        sys.exit("Please input correct arguments as: file.csv file.txt")

    # Dataset (as there are two different)
    dataset = str()

    # TODO: Read database file into a variable
    # Will do list of dictionaries
    csv_db = []
    with open(sys.argv[1]) as csv_file:
        reader = csv.DictReader(csv_file)
        # For each row, depending on the dataset, append key-value pairs where key is the str name and value is the number of such strs. Also, update the dataset variable for later convinience
        for row in reader:
            # print(row["name"],row["AGATC"],row["AATG"],row["TATC"])
            if len(row) == 4:
                dataset = "small"
                csv_db.append({"name": row["name"], "AGATC": row["AGATC"], "AATG": row["AATG"], "TATC": row["TATC"]})
            else:
                dataset = "large"
                csv_db.append({"name": row["name"], "AGATC": row["AGATC"], "TTTTTTCT": row["TTTTTTCT"], "AATG": row["AATG"],
                               "TCTAG": row["TCTAG"], "GATA": row["GATA"], "TATC": row["TATC"], "GAAA": row["GAAA"], "TCTG": row["TCTG"]})

    # TODO: Read DNA sequence file into a variable
    dna_sequence = str()
    with open(sys.argv[2]) as txt_file:
        dna_sequence = txt_file.read()

    # TODO: Find longest match of each STR in DNA sequence
    # Will try the format function (https://www.geeksforgeeks.org/python-string-format-method/) to get concatenated single "digit" for easy comparison
    # Depending on the used dataset, check different strs

    if dataset == "small":
        dna_combo = "{n1}{n2}{n3}".format(
            n1=longest_match(dna_sequence, "AGATC"),
            n2=longest_match(dna_sequence, "AATG"),
            n3=longest_match(dna_sequence, "TATC"))
    else:
        dna_combo = "{n1}{n2}{n3}{n4}{n5}{n6}{n7}{n8}".format(
            n1=longest_match(dna_sequence, "AGATC"),
            n2=longest_match(dna_sequence, "TTTTTTCT"),
            n3=longest_match(dna_sequence, "AATG"),
            n4=longest_match(dna_sequence, "TCTAG"),
            n5=longest_match(dna_sequence, "GATA"),
            n6=longest_match(dna_sequence, "TATC"),
            n7=longest_match(dna_sequence, "GAAA"),
            n8=longest_match(dna_sequence, "TCTG"))

    # print(dna_combo)

    # TODO: Check database for matching profiles
    # Placeholder for output text, default is "No match"
    output_text = "No match"
    for entry in csv_db:
        # For each dictionary item, access values and, depending on the dataset (as there are two), create dna combo for easy comparison
        if len(entry) == 4:
            current_dna_combo = "{s1}{s2}{s3}".format(s1=entry["AGATC"], s2=entry["AATG"], s3=entry["TATC"])
        else:
            current_dna_combo = "{s1}{s2}{s3}{s4}{s5}{s6}{s7}{s8}".format(
                s1=entry["AGATC"],
                s2=entry["TTTTTTCT"],
                s3=entry["AATG"],
                s4=entry["TCTAG"],
                s5=entry["GATA"],
                s6=entry["TATC"],
                s7=entry["GAAA"],
                s8=entry["TCTG"])

        # Update output text for the exit message
        if dna_combo == current_dna_combo:
            output_text = entry["name"]
            break

    print(output_text)
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
