# Scores 25/25 | 100%

[final_arrangement, ith] = [x for x in input().split(' ')]
ith = int(ith)

def getPossiblePreferences(car):
        """
        Get the list (ordered) of possible preferred spaces for the car-th car.
        E.g. getPossiblePreferences(0) gets the possible preferred spaces for Car a.
        Hence we know the first letter of all preference lists is just getPossiblePreferences(0).
        """
        
        # Get index of the car in the final arrangement
        car_position = final_arrangement.index(chr(car + 97))
        
        # Get the first possible preference as just the final position of the car       
        possible_preferences = [chr(car_position + 65)]
        
        # We count backwards from the car's position (index) to 0
        # as it is impossible for the car to have a later position as its preference
        for i in range(car_position - 1, -1, -1):
                # If the car in this position is a car that arrived earlier
                # then it is possible that this position was the car's preference
                if ord(final_arrangement[i]) < ord(final_arrangement[car_position]):
                        possible_preferences.append(chr(i + 65))
                else:
                        # The car arrived later and is in an earlier spot. Hence, the
                        # car's preference can't be this space or any earlier
                        break
                
        # Reverse the list as it will be backwards alphabetically
        # since we only add positions which are earlier
        return "".join(reversed(possible_preferences))

preferences_lookup = [getPossiblePreferences(n) for n in range(len(final_arrangement))]
first_letter = preferences_lookup[0]
preference_list = [first_letter]

def getLetter(n):
        """
        Adds the nth preference to preference_list and skips impossible preference lists.
        """

        global ith
        
        # If we have as many preferences as cars then we have finished
        if len(preference_list) == len(final_arrangement):
                return
        else:
                # Get the possible preferences for this car
                possible_preferences = preferences_lookup[n]
                
                # We are going to multiply this so initialise it as 1
                combinations_left = 1
                        
                # Work out number of combinations of preference lists from after this point
                for j in range(n + 1, len(final_arrangement)):
                        combinations_left *= len(preferences_lookup[j])
                
                # Check each preference at this position
                for k in range(len(possible_preferences)):       
                        if ith <= combinations_left:
                                # We know that the ith list lies in the set of possibilities using the kth
                                # possible preference at this position. It is important to remember that
                                # cars can have duplicate preferences.
                                preference_list.append(possible_preferences[k])
                                return getLetter(n + 1)
                        else:
                                # This means ith > combinations_left, so the list we're looking for lies
                                # in the set of possible lists using another letter in this position.
                                # We can therefore skip all lists using the kth possible preference at
                                # this position.
                                ith -= combinations_left
                                
                                
getLetter(1)
print("".join(preference_list))
