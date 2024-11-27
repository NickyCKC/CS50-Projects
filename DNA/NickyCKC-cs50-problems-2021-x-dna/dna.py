# Impport
from csv import reader, DictReader
from sys import argv, exit

def main():

    # Check command-line-arguments
    if len(argv) != 3:
        print("Usage: python dna.py data.csv sequence.txt")
        exit(1)

    database = argv[1]
    sequence = argv[2]

    # Open csv file
    with open(database, "r") as csvfile:
        # Create a dictionary
        reader = DictReader(csvfile)
        # Convert to list
        db_list = list(reader)

    with open(sequence, "r") as file:
        seq = file.read()

    # Highest count of consequtive STR chain
    max_count = []

    for i in range(1, len(reader.fieldnames)):
        STR = reader.fieldnames[i]
        max_count.append(0)

        for j in range(len(seq)):
            STR_count = 0

            # Find STR
            if seq[j:j + len(STR)] == STR:
                k = 0

                # Loop as long as chain is continuing
                while seq[(j + k):(j + k + len(STR))] == STR:
                    STR_count += 1
                    k += len(STR)

                # Update highest count
                if STR_count > max_count[i - 1]:
                    max_count[i - 1] = STR_count

    # Check for matches
    for i in range(len(db_list)):
        matches = 0

        for j in range(1, len(reader.fieldnames)):
            # Check if STR max count matches a person's STR's max count in sample list
            if int(max_count[j - 1]) == int(db_list[i][reader.fieldnames[j]]):
                matches += 1

            # Check if all STR of person matches
            if matches == len(reader.fieldnames) - 1:
                print(db_list[i]['name'])
                exit(0)

    # Check if no one matches
    print("No match")

main()