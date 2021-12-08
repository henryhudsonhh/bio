# Scores 25/25 | 100%

actors = int(input())
scenes = [int(x) for x in input().split(' ')]
totalScenes = sum(scenes)

sceneSchedules = []


def constructTree(currentScene, sceneAssignments):
    if currentScene == totalScenes + 1:
        sceneSchedules.append(sceneAssignments)
    else:
        available = getAvailableActors(sceneAssignments)
        for i in range(len(available)):
            newSceneAssignments = sceneAssignments.copy()
            newSceneAssignments[available[i]] += str(currentScene)
            newSceneAssignments[available[i]] += "|"
            constructTree(currentScene + 1, newSceneAssignments)


def getAvailableActors(sceneAssignments):
    available = []
    for actor in range(actors):
        acLength = len(sceneAssignments[actor].split("|"))-1
        if acLength < scenes[actor]:
            a = True
            for seniorActor in range(0, actor):
                if len(sceneAssignments[seniorActor].split("|"))-1 < acLength + 1:
                    a = False
            if a:
                available.append(actor)

    return available


builtDS = ["" for _ in range(actors)]

constructTree(1, builtDS)
print(len(sceneSchedules))
