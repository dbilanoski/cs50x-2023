# TODO
import re
# A program that first asks the user to type in some text, and then outputs the grade level for the text, according to the Coleman-Liau formula
# Coleman-Liau index is computed as 0.0588 * L - 0.296 * S - 15.8, where L is the average number of letters per 100 words in the text, and S is the average number of sentences per 100 words in the text

# Write Coleman-Liau score index function


def get_coleman_liau_index(avg_letters, avg_sentences):
    return round(0.0588 * avg_letters - 0.296 * avg_sentences - 15.8)


# Get inptut and convert it to lower case
sentence = input("Text: ").lower()

# Count letters, words and sentences
# For letters I'll do regex pattern matching only lowercase letters
letters = len(re.findall(r"[a-z]", sentence))
words = len(sentence.split(" "))
# For sentences I'll do regex pattern matching for ending symbols
sentences = len(re.split(r"[.!?]", sentence))-1

# Calculate averages of letters per 100 words and sentences per 100 words
avg_letters = letters * 100 / words
avg_sentences = sentences * 100 / words

# Run processed user input through Coleman-Liau function and get results
coleman_liau_score = get_coleman_liau_index(avg_letters, avg_sentences)

# Print sentence result based on assignment rules
if (coleman_liau_score < 1):
    print("Before Grade 1")
elif (coleman_liau_score > 16):
    print("Grade 16+")
else:
    print(f"Grade {coleman_liau_score}")
