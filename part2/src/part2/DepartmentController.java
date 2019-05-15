//Ilham Benzekri
//Ramon Moreta De la cruz
//Eliazar Contreras
//Jeuris De la Rosa
package part2;

import java.util.Random;
import java.util.concurrent.Semaphore;

public class DepartmentController {
    private static final int NUMBER_OF_STUDENTS = 6;

    /**
     * The main method
     * @param args
     */
    public static void main(String[] args) {
        //creating Random object to generate waiting times
        Random randomGenerator = new Random();
        // Create semaphores.
        WakeupSignal wakeupWakeupSignal = new WakeupSignal();
        Semaphore chairs = new Semaphore(3);
        Semaphore available = new Semaphore(1);

        //create NUMBER_OF_STUDENTS number of Student threads
        for (int i = 1; i <= NUMBER_OF_STUDENTS; i++) {
            // Create a new Student threads
            Thread student = new Thread(new Student(randomGenerator.nextInt(30) + 10, wakeupWakeupSignal, chairs, available, i));
            //start the thread
            student.start();
        }

        // Creating a TA Thread and starting it.
        Thread ta = new Thread(new TeachingAssistant(wakeupWakeupSignal, chairs));
        ta.start();
    }
}

/**
 * This class represents a Semaphore that will be used to wakeup the TeachingAssistant thread
 */
class WakeupSignal {
    private boolean signal = false;

    /**
     * This method notifies when the TeachingAssistant is woken up
     */
    public synchronized void take() {
        this.signal = true;
        this.notify();
    }

    /**
     * This method will keep the TeachingAssistant asleep until it is notified to awake
     * @throws InterruptedException
     */
    public synchronized void release() throws InterruptedException {
        while (!this.signal) wait();
        this.signal = false;
    }
}
