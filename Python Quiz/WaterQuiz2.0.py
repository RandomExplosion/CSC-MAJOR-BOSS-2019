QuestionsRight = 0
allowed = list("1234567890/")

def FindNotAllowed():
    for i in range(len(Answer)):
        if Answer[i] not in allowed:
            Answer[i] = ""

Correct = ""
def RightOrWrong():
    if Answer == Answers[QuestionsAnswered]:
        print("YOU WERE RIGHT!")
        #QuestionsRight += 1
        return True
    else:
        print("YOU WERE WRONG")
        print("THE ANSWER WAS " + Answers[QuestionsAnswered])

Answer = ""
QuestionsAnswered = int("0")
Questions = ["WHAT IS THE PERCENTAGE OF WATER ON THE SURFACE OF THE EARTH THAT CAN BE USED AS DRINKING WATER?", "WHAT FRACTION OF THE WORLD'S WATER IS SAFE DRINKING WATER?", "HOW MANY GIGALITRES OF WATER DOES AUSTRALIA USE PER YEAR?", "HOW MANY LITRES OF WATER DOES A PERSON HAVE TO DRINK EVERY DAY TO MAINTAIN A HEALTHY LIFESTYLE?", "HOW MANT TONNES OF WATER DOES THE SUN EVAPORATE EACH DAY ON AVERAGE?", "WHAT IS THE PERCENTAGE OF WATER THAT IS SOURCED FROM THE SURFACE?","WHAT IS THE PERCENTAGE OF WATER THAT IS SOURCED FROM GROUNDWATER?", "IF A TAP DRIPS ONCE EVERY SECCOND HOW MANY LITRES OF WATER DOES IT WAST PER DAY?", "HOW MANY LITRES OF WATER IS NEEDED TO GROW FOOD FOR A FAMILY OF FOUR?", "HOW MANY LITRES OF WATER DOES THE AVERAGE HOUSHOLD USE PER YEAR?", "WHAT IS THE PERCENTAGE OF WATER USED BY THE TOILET IN COMPARISON TO AN AVERAGE HOME?", "WHAT IS THE PERCENTAGE OF WATER USED BY THE KITCHEN IN COMPARISON TO AN AVERAGE HOME?", "WHAT IS THE PERCENTAGE OF WATER USED BY THE LAUNDRY IN COMPARISON TO AN AVERAGE HOME?", "HOW MANY LITRES OF WATER PRODUCES ONE CUP OF COFFE?"]
Answers = ["1", "1/4", "25000", "2", "1000000000000", "82", "18", "30", "25700", "24000", "23", "10", "16", "140"]
while QuestionsAnswered != 14:
    print(Questions[QuestionsAnswered])
    Answer = input("")
    FindNotAllowed()
    RightOrWrong()
    QuestionsAnswered = QuestionsAnswered + 1
#print("YOU GOT " + str(QuestionsRight) + " QUESTIONS RIGHT!")
print("GREAT JOB!")