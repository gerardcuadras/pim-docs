Queue Management & Workers
==========================

Job consumers
-------------

Akeneo PIM uses a daemon to execute jobs (i.e: imports, exports, etc.) from a queue.

This daemon is managed by ``systemd`` and allows multiple operations such as:

- start/restart a daemon
- check the status of a daemon
- see logs of a daemon

Please note that, while the number of running job consumers is not enforced, it is not recommended
to increase it above the server capability. Between 1 and 3 comsumers is recommended.

As of PIM 3.1, each daemon can be dedicated to run certain job(s), hence making sure the jobs will
be executed in a timely manner, and that their execution will not interfere with other business
operations.

Configurations of daemons are stored under `/home/akeneo/.systemd/pim_job_queue`.

Each text file contains the list of supported jobs for a given queue.

Example in file `/home/akeneo/.systemd/pim_job_queue/1.conf`:

.. code-block:: bash
   :linenos:

   csv_product_export
   csv_category_export
   csv_family_export

The name of the file is the **daemon identifier**. Make it simple and use only integer numbers.

.. code-block:: bash
   :linenos:

   # Launch the daemon for this configuration /home/akeneo/.systemd/pim_job_queue/1.conf
   partners_systemctl pim_job_queue@1 start

   # Check the status of the daemon #2
   partners_systemctl pim_job_queue@2 status

   # Check the status of all daemons
   partners_systemctl pim_job_queue@* status


Please note that if **no configuration** file exist for a given daemon identifier,
the daemon will consider that it has to consume **any** elements in the queue. This is the default
behavior.

Onboarder
---------

While Onboarder requires workers to run at all times, those are disabled by default since some customers do not use the Onboarder.

Learn more about the onboarder and its configuration in the PIM in the dedicated section :doc:`/onboarder/index`.

.. code-block:: bash
   :linenos:

   # Enable one worker
   partners_systemctl pim_onboarder_worker@1 start

   # Start the worker
   partners_systemctl pim_onboarder_worker@1 start

   # Check the status of the daemon #2
   partners_systemctl pim_onboarder_worker@1 status

   # Stop pim_onboarder_worker
   partners_systemctl pim_onboarder_worker stop
