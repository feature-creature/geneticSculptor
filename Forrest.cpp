#include "Forrest.h"

//-------------------------------------------------------
Forrest::Forrest() {
}

//-------------------------------------------------------
void Forrest::setup(float m, int num)
{
    // initialize global mutation rate 
    mutationRate = m;

    // prepare for current generation by
    // empty/clear the tree vector of any previously stored tree objects
    trees.clear();

    // fill the empty tree vector with temporary tree objects
    for (int x=0; x<num; x++){
        // initialize a tree object 
        Tree tempTree;
        // gene (not DNA) version of setup function
        tempTree.setup(16);
        // store the new tree in the tree vector
        // ?? not pointers etc
        trees.push_back(tempTree);
    }

}

//-------------------------------------------------------
// Generate a mating pool
// designate a sub population of the current population (mating pool)
// for selecting the possible parents for the next generation of trees 
void Forrest::selection() {
    
    // empty/clear the mating pool vector of any previously stored tree objects
    matingPool.clear(); 

    // clear the previously stored 'total mating quantity' for the entire previous mating pool vector 
    // this value is used to determine the individual tree's probability for mating in relation to the whole pool
    float maxFitness=0;

    // sum the total mateability of the current mating pool vector
    for(int i = 0; i < trees.size(); i++) maxFitness += trees[i].fitness;
    
    // create the mating pool of the current population for generating the next generation
    // first determine % 'mateability' for each current individual in relation to the total current population 
    // then create mating pool by adding each current individual with a non-zero mateability number to the mating pool
    // probabilities are created in the mating pool by adding those non-zero individuals to the pool 
    // multiple times (exactly as many times as their mateability number). 
    // 2 parents will be chosen from this probabilistic mating pool to generate the next generation of trees
    // higher percent == higher chance for mating -- only 2 get to mate
    for (int i = 0; i < trees.size(); i++) {
        // normalize fitness values on 0-1 scale
        float fitnessNormal = ofMap(trees[i].fitness, 0, maxFitness, 0, 1);
        // normalize fitness values on 0-100 scale
        int n = (int) (fitnessNormal * 100);
        // if the individual has a non-zero n value, add individual n times into mating pool
        for (int j = 0; j < n; j++) {
            matingPool.push_back(trees[i]);
        }

    }
    // mating pool is now populated for selection
}

//------------------------------------------------------------
// display the current generation of the forrest
// draw each tree
void Forrest::draw(){
    for(int i =0; i < trees.size(); i++)
    {
        // tree
        trees[i].draw(0,0);
        ofSetColor(0);
        // tree's fitness value
        ofDrawBitmapString(ofToString(i) + ":" + ofToString(trees[i].fitness), -10, 20);
        // to correctly position the next tree in the window, translate 1/num of trees distance to the right 
        ofTranslate(ofGetWidth()/trees.size(), 0);
    }
}

//------------------------------------------------------------
// Create a new generation of trees and
// fill the tree vector with them 
void Forrest::generate() {

    for (int i = 0; i < trees.size(); i++) {

        // (at random) choose two trees from the mating pool
      int a = int(ofRandom(matingPool.size()));
      int b = int(ofRandom(matingPool.size()));

        // store the selected trees as two temporary local tree objects
      Tree partnerA = matingPool[a];
      Tree partnerB = matingPool[b];
      
      // create a temporary local DNA object with the temporary local genotype data
      DNA childDNA = partnerA.dna.crossover(partnerB.dna);

      // ?? why is this necessary (here)
      // decodes the currently stored tree's geneotype data into
      // variables for visual phenotype representation
      // !!works without it
      //trees[i].calcPhenotype();
      
      // mutate the child dna for child variability
      childDNA.mutate(mutationRate);

      // create temporary local tree object 
      Tree child;
        //set it up with the temporary local DNA data 
      child.setup(childDNA);

      // replace the currently stored tree
      // by storing this local temporary tree in its place
      trees[i] = child;
      
      // decodes the newly stored tree's geneotype data into
      // variables for visual phenotype representation
      trees[i].calcPhenotype();
    }
}

//------------------------------------------------------------
void Forrest::pick(int n){
     trees[n].fitness++;
}
