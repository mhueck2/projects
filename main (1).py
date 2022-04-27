'''
Max Huecksteadt 
CS 541 

This is Programming Assignment #2, the GA implementation of the 8 queens game.
'''
import numpy as np
import random
import matplotlib
matplotlib.use('TkAgg')
import matplotlib.pyplot as plt

NumIterations = 100
PopSize = 10
MutationPct = 15

# Fitness function defined as # of non-attacking queens on board [0 to 28 max]
def fitness(board): 
  noConflict = 0
  for i in range(8):
    for j in range(i+1,8):
      if (board[i] != board[j]) and (abs(j-i) != abs(board[i]-board[j])): 
        noConflict += 1
  return noConflict

# Parent class to generate random board and calculate fitness for each member 
class Parent: 
  def __init__(self):
    self.board = list(np.random.randint(8,size=8))
    self.fit = fitness(self.board)

# Create population list (of 'parent class' members) 
def initializePop(): 
  population = [Parent() for i in range(PopSize)]
  return population

# Generate fitness sum and normalized fitness distribution for population, also return average population fitness 
def getProbs(population):
  fitSum = sum(parent.fit for parent in population)
  parentProbs = [parent.fit/fitSum for parent in population]
  avg = (fitSum/PopSize)
  return parentProbs, avg

# Crossover function: swap parent boards across randomly generated point
def crossover(parents):
  crosspt = random.randint(0,7)
  child1, child2 = Parent(), Parent()
  parent1 = parents[0].board
  parent2 = parents[1].board

  child1.board[0:crosspt],child1.board[crosspt:] = parent1[:crosspt], parent2[crosspt:]
  child2.board[0:crosspt],child2.board[crosspt:] = parent2[:crosspt], parent1[crosspt:]
  child1.fit = fitness(child1.board)
  child2.fit = fitness(child2.board)
  return child1, child2 

# Chance of randomly mutating one gene in the child chromosome to random value
def mutate(child):
  if (random.randint(0,100) < MutationPct):
    gene = random.randint(0,7)
    val = random.randint(0,7)
    child.board[gene] = val 
  return child

# Randomly sample 2 parents from fitness distribution, cross genes and mutate 
def parentSelect(population, probList):
  children = []
  for i in range(0, len(population), 2):
    selection = np.random.choice(population, size=2, replace=False, p=probList)
    child1, child2 = crossover(selection)
    child1 = mutate(child1)
    child2 = mutate(child2)
    children.append(child1)
    children.append(child2)
  return children 

# Print population 
def printPop(population, avg, genNum):
  for child in population:
    print(child.board, child.fit)
  print ("avg fitness:", avg, "Generation #:", genNum)
  print()



############################
# Driver Code
############################
# First children from randomly initialized population: 
initPop = initializePop()
parentProbs, popAvg = getProbs(initPop)
printPop(initPop, popAvg, 0)
children = parentSelect(initPop, parentProbs)

genNumber = 0
generations=[0]
solution = False 
avgFitnesses=[]
avgFitnesses.append(popAvg)

# Loop through until solution found (one child fitness =28), or avg fitness = 28
for i in range(NumIterations): 
  genNumber += 1
  generations.append(genNumber)
  population = children 
  fitProbs, popAvg = getProbs(population)
  children = parentSelect(population, fitProbs) 
  printPop(children,popAvg, genNumber)
  avgFitnesses.append(popAvg)
  for child in children:
    if child.fit == 28:
      print("Solution:", child.board)
      solution = True 
  if popAvg == 28 or solution == True:
    break 

#for i in range(len(fitnesses)):
 # print(fitnesses[i])
print("Max population avg fitness and index:")
print(max(avgFitnesses), avgFitnesses.index(max(avgFitnesses)))

plt.plot(generations, avgFitnesses)
plt.xlabel("Generations")
plt.ylabel("Average Fitness")
plt.xlim([0, NumIterations])
plt.ylim([0, 28])
plt.show()
