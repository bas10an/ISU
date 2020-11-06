
Mutex m;
condition entry;
condition exit;

bool PLCS_ENTRY_IS_OPEN = false;
bool PLCS_EXIT_IS_OPEN = false;
bool carWaiting = false;

PLCS_entry{
    lock(m);

    while(!carWaiting)
        condWait(entry, m);

    openPLCS_ENTRY();
    PLCS_ENTRY_IS_OPEN = true;
    condSignal(entry);
    while(carWaiting)
        condWait(entry, m);
    
    closePLCS_ENTRY();
    PLCS_ENTRY_IS_OPEN = false;
    unlock(m);
}

PLCS_exit{
    lock(m);

    while(!carWaiting)
        condWait(exit, m);

    openPLCS_EXIT();
    PLCS_EXIT_IS_OPEN = true;
    condSignal(exit);
    while(carWaiting)
        condWait(exit, m);
    
    closePLCS_EXIT();
    PLCS_EXIT_IS_OPEN = false;
    unlock(m);
}

CAR{
    /*.. Entry ..*/
    lock(m);
    carWaiting = true;
    condSignal(entry);

    while(!PLCS_ENTRY_IS_OPEN)
        condWait(entry, m);

    /*.. Drive in ..*/
    carWaiting = false;
    condSignal(entry);
    unlock(m);

    /*.. Entered and waiting before Exiting ..*/
    sleep(5);

    /*.. Exit ..*/
    lock(m);
    carWaiting = true;
    condSignal(exit);

    while(!PLCS_EXIT_IS_OPEN)
        condWait(exit, m);

    /*.. Drive out ..*/
    driveOutofGarage();
    carWaiting = false;
    condSignal(exit);
    unlock(m);
}

main{
    thread car;
    thread PLCS_entry;
    thread PLCS_exit;

    thread_create(PLCS_entry);
    thread_create(PLCS_exit);
    thread_create(car);
}