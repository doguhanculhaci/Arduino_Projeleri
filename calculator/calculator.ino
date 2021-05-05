float num1, num2;

float answer;

char op;

bool first_value = false;
bool second_value = false;
bool answer_value = false;
bool control = false;


void setup()
{
  Serial.begin(9600);
  
}

void loop()
{
  
  if(!first_value)
  {
    if(!control)
    {
      Serial.print("First value = ");
      control = true;
    }
    
    while(Serial.available() > 0)
    {
      num1 = Serial.parseFloat();
      
      
      Serial.println(num1,2);
      
      first_value = true;
    }
    
    
    if(num1 >= 100 && first_value)
    {
      Serial.print("The value entered must be less than 100. Try again = ");
      
      first_value = false;
    }
  }
  else if(!second_value)
  {
    if(control)
    {
      Serial.print("Second value = ");
      control = false;
    }
    
    while(Serial.available() > 0)
    {
      num2 = Serial.parseFloat();
      
      Serial.println(num2,2);
      
      second_value = true;
    }
    
    if(num2 >= 100 && second_value)
    {
      Serial.print("The value entered must be less than 100. Try again = ");
      
      second_value = false;
    }
  }
  else if(!answer_value)
  {
    if(!control)
    {
      Serial.print("Operation = ");
      control = true;
    }
    
    while(Serial.available() > 0)
    {
      op = Serial.read();
      
      Serial.println(op);
      
      answer_value = true;
    }
    
    if (op == '+')
    {
      answer = num1+num2;
      
      Serial.println(answer,2);
    }
    else if (op == '-')
    {
      answer = num1-num2;
      
      Serial.println(answer,2);
    }
    else if (op == '*')
    {
      answer = num1*num2;
      
      Serial.println(answer,2);
    }
    else if (op == '/')
    {
      answer = num1/num2;
      
      Serial.println(answer,2);
    }
    
    else if(answer_value)
    {
      Serial.print("Entered transaction is incorrect.Try again = ");
      
      answer_value = false;
    }
  }
  else
  {
    Serial.println("NEW CALCULATION BEGINS");
    
    num1 = 0; 
    num2 = 0;

  answer = 0;

  op = 0;

  first_value = false;
  second_value = false;
  answer_value = false;
  control = false;
  }
}
