//Ilham Benzekri
//Ramon Moreta De la cruz
//Eliazar Contreras
//Jeuris De la Rosa
package part2;
import java.util.concurrent.Semaphore;

/**
 * TeachingAssistant class which represents Teaching Assistant thread who will help Students
 */
class TeachingAssistant implements Runnable {
    //declaring class instance variables
    private Thread currentThread;
    private WakeupSignal wakeup;
    private Semaphore chairs;

    /**
     * Class constructor which creates a new Student object
     *
     * @param wakeupSignal Semaphore to wakeup the teaching assistant
     * @param chairs       Semaphore which represents the available chairs
     */
    public TeachingAssistant(WakeupSignal wakeupSignal, Semaphore chairs) {
        wakeup = wakeupSignal;
        this.chairs = chairs;
        currentThread = Thread.currentThread();
    }

    @Override
    public void run() {
        while (true) {
            try {
                System.out.println("Currently there are no Students waiting. The TA will now take a nap");
                wakeup.release();
                System.out.println("The TA is now awake");
                currentThread.sleep(7000);

                //check if there Student waiting
                if (chairs.availablePermits() != 3) {
                    //help all students waiting
                    do {
                        currentThread.sleep(7000);
                        //release the chair
                        chairs.release();
                    }
                    while (chairs.availablePermits() != 3);
                }
            } catch (InterruptedException e) {
                continue;
            }
        }
    }
}
