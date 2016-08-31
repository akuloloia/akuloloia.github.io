import java.util.*;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.PrintWriter;

/*
*Create a mini-telephone directory using a hash table with separate chaining.
*@author Kuloloia, Anthony
*@assignment ICS 211 Project
*5/8/14
*/

public class KuloloiaAnthonyProject
{
   public static void main (String [] args)
   {
      //error checking is done here
      //if the user does not enter exactly two arguments in the run arguments textbox, they are shown this message
      if(args.length != 2)
      {
         System.out.print( "Please enter two file names.\nThe first is the input file and the second is the output file.");
      }
      
      //otherwise this will execute
      else
      {
         //variables utilized in the main method are initialized here
         File file = new File(args[0]);
         Scanner scan = null;
         Integer skip = new Integer(0);
         boolean askAgain = false;
         String input = new String("");
         int inputNum = 0;
         String name = "";
         String teleNumber = "";
         TelephoneBook book = new TelephoneBook();
         PersonNode newPers = new PersonNode(name, teleNumber, null);
         int choice = 0;
         try
         {
            scan = new Scanner(file);
         }
         //if the scanner can't locate the file, this error will popup
         catch(FileNotFoundException e)
         {
            System.out.print( "Could not find file: \"" + args[0] + "\".  Please try again.");
         }
         
         //this loop will continue to run as long as the scanner object has another line of input to read
            try
            {
            System.out.println("Reading from input file: " + args[0]);
            Scanner tokenIn = new Scanner(file).useDelimiter(",|\\s");
            Scanner nextLine = new Scanner(tokenIn.nextLine());
            while(tokenIn.hasNextLine())
            {
               //skips first line of csv file
               if(skip == 0)
               {
                  skip++;
               }
               else
               {
               //Scanner variable that separates the name from the telephone number
               name = tokenIn.next();
               teleNumber = tokenIn.next();
               newPers = new PersonNode(name, teleNumber, null);
               book.insert(newPers);
               tokenIn.next();
               }
               
            }
            }
            //if the scanner reads nothing, this statement will catch the error
            catch(NoSuchElementException e)
            {
            
            }
            catch(FileNotFoundException e2)
            {
               System.out.print( "Could not find file: \"" + args[0] + "\".  Please try again.");
            }
            Scanner numInput = new Scanner(System.in);
            System.out.print("\nPersonal Telephone Book Hash Table\n");
            while(askAgain == false)
            {
               try{
               //Displays main menu
                  System.out.print("\nMAIN MENU\n1. Insert telephone number\n2. Retrieve telephone number\n3. Delete telephone number\n4. Display telephone number\n5. End program\nEnter choice (1-5): ");
                  choice = numInput.nextInt();
                  }
                  catch(InputMismatchException e)
                  {
                     numInput.next();
                  }                
                  scan = new Scanner(System.in);
                  //inserts new person into telephone hashtable
                  if(choice == 1)
                  {
                     System.out.print("\nEnter person's name: ");
                     name = scan.next();
                     System.out.print("Enter person's telephone number: ");
                     teleNumber = scan.next();
                     PersonNode person = new PersonNode(name, teleNumber, null);
                     book.insert(person);
                  }
                  //retrieve person's telephone number
                  else if(choice == 2)
                  {
                     System.out.print("\nEnter person's name: ");
                     name = scan.next();
                     teleNumber = book.retrieve(name);
                     System.out.println("The telephone number is: " + teleNumber);
                  }
                  //delete person from telephone hashtable
                  else if(choice == 3)
                  {
                     System.out.print("\nEnter person's name: ");
                     name = scan.next();
                     String output = book.delete(name);
                     System.out.print(output);
                  }
                  //displays all names and ages found within the input file
                  else if(choice == 4)
                  {
                     System.out.print("\n" + book.toString());
                  }
                  //ends program and writes output the output file
                  else if(choice == 5)
                  {
                     PrintWriter fileWriter = null;
                     try 
                     {
                        fileWriter = new PrintWriter(args[1]);
                     } 
                     catch (FileNotFoundException exception) 
                     {
                        System.out.print("ERROR: File not found for \"" + args[1] + "\"");
                     }
                     //if a connection to the file is made, the following code will run
                     if(fileWriter != null){
                     //loop through queue and write to file
                        fileWriter.println(book.toString());
                        System.out.print("\nWrote to file \"" + args[1] + "\"");
                        fileWriter.close();
                     }
                     askAgain = true;
                  }
                  else
                  {
                     System.out.println("\nYou did not enter a choice between 1 and 5.  Please try again.");
                  }
               }
            }
            
         }

      }
   


      class LinkedList
      {
         private PersonNode head = null;
         private Integer size = new Integer(0);
         
         /**
         *creates a new PersonNode object and adds that object to the end of the LinkedList
         *@param nameP: is the name of the PersonNode object
         *@param ageP: is the age of the PersonNode object
         */
         public void add(String nameP, String numberP)
         {
            //if the top of the linked list is empty, the PersonNode is added
            if(head==null)
            {
               head = new PersonNode(nameP, numberP, null);
            }
            else
            {
               PersonNode temp = new PersonNode(nameP, numberP, null);
               temp.setNext(head);
               head = temp;
            }
            size = size + 1;
         }
         
         /**
         *finds person node object based on user input
         *@param nameP: is the name of the PersonNode object
         *@return number of the corresponding person
         */
         public String get(String nameP)
         {
            String people = "";
            Integer location = new Integer(1);
            //iterates through the linked list from the first to the last individual            
            for(PersonNode current = head; current != null; current = current.getNext())
            {
               String nextName = current.getName();
               //if the age the user inputted matches the age of the individual found in the link list, it is stored to the people string
               if(nextName.equals(nameP))
               {
                  people = people + current.getTelephoneNumber() + "\n";
                  location++;
               }
               //otherwise it will move to the next individual
               else if (nextName != nameP)
               {
                  location++;
               }
            }    
            //if the age the user inputs matches no individuals in the linked list, they are shown this message
            if(people.equals(""))
            {
               people = people + "There are no matching numbers for name " + nameP;
               return people;
            }
            //otherwise all individuals who matched the age the user inputted will be returned
            else
            {        
               return people;
            }
         }
         
         /*Removes name of item being passed as parameter
         *@param	name of item to be removed
         */
         public void remove(String nameP)
         {
             PersonNode currentNode = head;
             while(currentNode.getNext()!= null)
             {
                 //if the name equals the head node, the following code will execute
                 if(head.getName().equals(nameP))
                 {
                     if(head != null)
                     {
                        PersonNode temp = head.getNext();
                        head = head.getNext();
                        size--;
                     }
                 }
                 //if the name equals any node besides the head, the following code will execute
                 else if(currentNode.getNext().getName().equals(nameP))
                 {
                     if(currentNode != null && currentNode.getNext() != null)
                     {
                        PersonNode temp = currentNode.getNext();
                        currentNode.setNext(currentNode.getNext().getNext());
                        size--;
                     }
                 }
                 //otherwise it will move to the next node
                 else
                 {
                     currentNode = currentNode.getNext();
                 }
             }
         }


         
         /**
         *toString method that returns a string displaying the toString output for each PersonNode object on a separate line
         *@return a String to display to the user
         */
         public String toString()
         {
            String output = new String("");
            Integer location = new Integer(1);
            
            //iterates through the linked list and stores each individual to the output variable
            for(PersonNode current = head; current != null; current = current.getNext())
            {
               if(current==null)
               {
                 output = output + " null";
               }
               else
               {
                  output = output + current.toString() + " => ";
                  location++;
               }
            }
            output = output + "null";
            return output;
         }
         
      }
      
      class PersonNode
      {
      
         //data fields are created here
         private String name = new String("");
         private String telephoneNumber = new String("");
         private PersonNode next;
         
         /**
         *Constructor method (Initializes data fields created above)
         *@param nameP: initializes name variable
         *@param ageP: initializes age variable
         *@param nextP: initializes next variable
         */
         public PersonNode(String nameP, String numberP, PersonNode nextP)
         {
            name = nameP;
            telephoneNumber = numberP;
            next = nextP;
         }
         
         /**
         *toString method that displays the name and age of each person within the format "X is Y years old."
         *@return a String to display to user
         */
         public String toString()
         {
            String display = (name + " " + telephoneNumber);
            return display;
         }
         
         /**
         *Get method that gets a data field from above
         *@return the location of the next node
         */
         public PersonNode getNext()
         {
            return next;
         }
         
         /**
         *Set method that sets a data field to new input data
         *@param dataP: points to a node which is then set to the variable "next"
         */
         public void setNext(PersonNode nextP)
         {
            next = nextP;
         }
         
         /**
         *Get method that gets the name data field
         *@return the name of that PersonNode
         */
         public String getName()
         {
            return name;
         }
         
         /**
         *Get method that gets the telephone number data field
         *@return the telephone number of that PersonNode
         */
         public String getTelephoneNumber()
         {
            return telephoneNumber;
         }
       }  
       
       
       class TelephoneBook
       {
         //array of 7 linkedlist elements
         int size = 7;
         LinkedList[] people = new LinkedList[size];
         
         /*Constructor method (initializes the data fields created above)
         */
         public TelephoneBook()
         {
            int start = 0;
            while(start<size)
            {
               if(people[start] == null)
               {
                  people[start] = new LinkedList();
                  start++;
               }
            }
         }
         
         /**
         *adds a new PersonNode object to the end of the Hash table
         *@param personP: is the person node being added
         */
         public void insert(PersonNode personP)
         {
            //get the name and number for the person node paramter
            String name = personP.getName();
            String number = personP.getTelephoneNumber();
            //converts the name into a hash code
            Integer stringHash = name.hashCode();
            Integer myHash = (stringHash%7);
            //stores into the hash table based on separate chaining
            for(int i=0;i<size;i++)
            {
               if(myHash>=0 && myHash<7 && myHash == i)
               {  
                  people[i].add(name, number);
               }
            }     
         }
         
         /**
         *Get method that gets the number data field from the string parameter
         *@param personP = is the name of the person we are retrieving the number for
         *@return the number of that PersonNode
         */
         public String retrieve(String personP)
         {
            String number = "";
            //converts name of the string parameter into a hash code
            Integer name = personP.hashCode();
            Integer match = name%7;
            //iterates through hash table until it finds name
            for(int i=0;i<size;i++)
            {
               if(match==i)
               {
                  number = people[i].get(personP);
               }
            }
            //returns the phone number that corresponds to the personP parameter
            return (number);
         }
         
         /*Removes name of item being passed as parameter
         *@param	name of item to be removed
         *@returns the string "Deleting: " + phone number of the person being deleted
         */
         public String delete(String personP)
         {
            String output = "";
            //converts string parameter into hash code
            Integer name = personP.hashCode();
            Integer match = name%7;
            //iterates through hash table until it finds the person
            for(int i=0;i<size;i++)
            {
               
               if(match==i)
               {
                  //removes that person from the hash table
                  output = people[i].get(personP);
                  people[i].remove(personP);
               }
            }
            return "Deleting: " + personP + " " + output;
         }
         
            
         /**
         *toString method that returns a string displaying the toString output for each person in the hash table based on separate chaining
         *@return a String to display to the user
         */
         public String toString()
         {
            String output = "DISPLAY TABLE\n";
            //iterates through hash table
            for(int i=0;i<size;i++)
            {
               output = output + "table ["+i+"] => " +people[i]+ "\n";             
            }
            
            return output;
         }
         
       }