# Scores 25/25 | 100%

[final_arrangement, ith] = [x for x in input().split(' ')]
ith = int(ith)

def getPossiblePreferences(car):
        car_position = final_arrangement.index(chr(car + 97))   
        possible_preferences = [chr(car_position + 65)]
        
        for i in range(car_position - 1, -1, -1):
                if ord(final_arrangement[i]) < ord(final_arrangement[car_position]):
                        possible_preferences.append(chr(i + 65))
                else:
                        break

        return "".join(reversed(possible_preferences))

preferences_lookup = [getPossiblePreferences(n) for n in range(len(final_arrangement))]
first_letter = preferences_lookup[0]
preference_list = [first_letter]

def getLetter(n):
        global ith
        if len(preference_list) == len(final_arrangement):
                return
        else:
                possible_preferences = preferences_lookup[n]
                combinations_left = 1
                
                for j in range(n + 1, len(final_arrangement)):
                        combinations_left *= len(preferences_lookup[j])
                
                for k in range(len(possible_preferences)):       
                        if ith <= combinations_left:
                                preference_list.append(possible_preferences[k])
                                return getLetter(n + 1)
                        else:
                                ith -= combinations_left
                                
getLetter(1)
print("".join(preference_list))
