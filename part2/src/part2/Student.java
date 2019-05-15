//Ilham Benzekri
//Ramon Moreta De la cruz
//Eliazar Contreras
//Jeuris De la Rosa
package part2;
import java.util.concurrent.Semaphore;

/**
 * Student class which represents a Student thread.
 */
class Student implements Runnable {
    //declaring class instance variables
    private int waitTime;
    private int studentNumber;
    private Semaphore available;
    private WakeupSignal wakeup;
    private Semaphore chairs;
    private Thread currentThread;


    /**
     * Class constructor which creates a new Student object
     *
     * @param wakeupSignal  Semaphore to wakeup the teaching assistant
     * @param chairs        Semaphore which represents the available chairs
     * @param available     Semaphore to to determine if Teaching Assistant is available
     * @param studentNumber Student number
     */
    public Student(int waitTime, WakeupSignal wakeupSignal, Semaphore chairs, Semaphore available, int studentNumber) {
        this.waitTime = waitTime;
        wakeup = wakeupSignal;
        this.chairs = chairs;
        this.available = available;
        this.studentNumber = studentNumber;
        currentThread = Thread.currentThread();
    }

    @Override
    public void run() {
        //loop infinitely
        while (true) {
            try {
                System.out.println("Student " + studentNumber + " has started programming for " + waitTime + " seconds.");
                //convert waiting time to milliseconds
                currentThread.sleep(waitTime * 1000);
                // after programming check if teaching assistant is available
                System.out.println("Student " + studentNumber + " has finished programming and is now checking if the TA is available.");

                if (available.tryAcquire()) {
                    try {
                        //the TA is available. Wake him up
                        wakeup.take();
                        System.out.println("Student " + studentNumber + " has woke up the TA to ask for help and is now being helped");
                        currentThread.sleep(7000);
                        System.out.println("Student " + studentNumber + " has been helped by the TA. The TA is now free waiting for another Student");
                    } catch (InterruptedException e) {
                        continue;
                    } finally {
                        //release the TA
                        available.release();
                    }
                } else {
                    //the TA currently helping another student Check to see if any chairs are available.
                    System.out.println("Student " + studentNumber + " has found the TA helping another student and is now looking for a chair in the hallway");
                    if (chairs.tryAcquire()) {
                        try {
                            //Student now waiting fo the TA to finish helping the other students who came before
                            System.out.println("Student " + studentNumber + " is sitting in the hallway waiting for " + (3 - chairs.availablePermits()) + " Student(s) to be served");
                            available.acquire();
                            System.out.println("Student " + studentNumber + " is now being helped by the TA");
                            currentThread.sleep(7000);
                            System.out.println("Student " + studentNumber + " has been helped by the TA. The TA is now free waiting for another Student");
                            available.release();
                        } catch (InterruptedException e) {
                            continue;
                        }
                    } else {
                        //no seats available
                        System.out.println("Student " + studentNumber + " has not found a chair in the hallway. Walking away to continue programming");
                    }
                }
            } catch (InterruptedException e) {
                break;
            }
        }
    }
}

