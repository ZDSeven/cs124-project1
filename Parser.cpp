Parser 
current = 0
tokens

match(TokenType type) -> bool { 
  If (tokens[current].type == type) { 
     Current += 1 
     Return true 
  }
  Return false 
}

Primary -> Negated Sentence  | Atomic 



AND
OR
IMPLIES
EQUIVALENT

P EQUIVALENT Q IMPLIES S AND T

parseSentence() -> Sentence 
  -> parseCompound() 

parseCompound() 
   Return parseEquvalent()


parseEquivalent() 
 // P
   expr = parseImplies() 

    While (match(Equivalent) {  
       Operator = previous(); 
       Right = parseImplies();
      // P EQUIVALENT  (Q IMPLIES (S AND T))
       Expr = CompoundSentence(expr,  operator, right);
 } 
 Return expr;
}



parseImplies() 
 // Q
   Expr = parseOr(); 

   While (match(Implies)) { 
   Operator = previous();  
    // S AND T
    Right = parseOr();
    Expr = Compound(expr, operator, right);
  } 
} 

 } 
… 

parseOr() {  
Expr = parseAnd(); 

 While (match(Or) {  
       Operator = advance(); 
       Right = parseAnd();
       Expr = CompoundSentence(expr,  operator, right);
 } 
Return expr;
}

parseAnd() {  

// S
Expr = parsePrimary(); 

 While (match(And) {  
       Operator = advance(); 
       // T
       Right = parsePrimary();
       Expr = CompoundSentence(expr,  operator, right);
 } 
Return expr;
}

Primary := Grouped | Negated | Variable | True | False

parsePrimary() { 
  If (match(LeftParent)) {  
   Return parseGrouped();
 } 

If (match(Not)) {
  Return parseNegated();
}



Return parseAtomic();
}

parseAtomic() -> Sentence { 
  If (match(True) or match(False)) {   
   Return Value(previous());
}
 If (match(Variable) { 
   Return Variable(previous());
}
Return error
}

parseGrouped() -> Sentence {
  sentenceInside = parseSentence();
  If (not match(RightParen) { 
    Raise Error();
} 
  Return Grouped(sentenceInside);
}

P IMPLIES Q AND S
( P IMPLIES Q) AND S

-> Sentence 

class Sentence { 

  virtual void evaluate() {}

}


class CompoundSentence : Sentence { 

   Void evaluate() override { }
}

class NegatedSentence : Sentence { 

   Void evaluate() override { 

   }
}

class AtomicSentence : Sentence { 

   Void evaluate() override { }
}

vector<Sentence> sentences; 

sentences.push_back(AtomicSentence());
sentences.push_back(NegatedSentence());







