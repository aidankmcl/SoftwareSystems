"""This file contains code for the database implementation
portion of homework 3 of Olin's Software Systems class. The
code below communicates our logic for finding the "Bacon
Number" between two actors by actor to movie and movie to
actor mapping with MongoDB

Written by Aidan McLaughlin, Deborah Hellen, Rahil Dedhia, Charlene Lee
"""

from pymongo import MongoClient
import sys

client = MongoClient()
db = client.imdb

movies = db.mov  #list of movies
acts = db.acts           #actors/actresses

"""Takes a list of actors and makes a list of all the movies they're
featured in. It then returns a tuple that contains the aList and
mList. aList cleared for population in the next step."""

def actor_to_movie(amListTuple):
        aList = amListTuple[0]
        for i in aList:
                for movies in i["mov"]:
                        mList.append(movies)
        aList = []
        return (aList,mList)

"""Does the reverse of the above function, however the context below
is important. Once the list of actors/actresses is made we check if
the target matches any of the strings in the aList. If yes, our
querying is complete. Otherwise, the number of steps is incremented
and the loop continues."""

def movie_to_actor(amListTuple):
        mList = amListTuple[1]
        for i in mList:
                for actors_actresses in i["name"]:
                        aList.append(actors_actresses)
        mList = []

        return (aList,mList)

def main():
    stepsToBacon = 1
        #  full actor name from input
        base = str(input("Name to launch from? "))
        target = "Bacon, Kevin (I)" # assuming Oracle of Bacon

        #  finds all objects with same name as base; should be one
        aList = acts.find({"name": base})
        mList = []

        #  iterative Tuple, used to pass two pieces of data around.
        iTuple = (aList,mList)

        #  Main loop
        for i in range(10):
                # Begins with actor to movie
                if i % 2 == 0:
                        iTuple = actor_to_movie(iTuple)
                        continue
                elif i % 2 != 0:
                        iTuple = movie_to_actor(iTuple)
                        if target in iTuple[0]:
                                print("Made it to Bacon in "+str(stepsToBacon)+" steps!")
                                break
                        else:
                                print("Not yet :(")
                                stepsToBacon++

if __name__ == '__main__':
    main()