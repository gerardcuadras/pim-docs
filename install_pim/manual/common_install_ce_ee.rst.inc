Initializing Akeneo
-------------------

Configure the PIM via the ``.env`` file:

.. code-block:: yaml
    :linenos:

    APP_ENV=prod
    APP_DATABASE_HOST=localhost
    APP_DATABASE_PORT=null
    APP_DATABASE_NAME=akeneo_pim
    APP_DATABASE_USER=akeneo_pim
    APP_DATABASE_PASSWORD=akeneo_pim
    APP_INDEX_HOSTS='localhost:9200'


Launching the PIM in dev mode
-----------------------------

.. note::

   All `make` commands must be run from the PIM root directory, either created by the archive or from the composer create project above.


To run the PIM EE in dev mode without docker, you will need to change some configuration files:

.. code-block:: bash

    $ cp vendor/akeneo/pim-enterprise-dev/config/packages/prod_onprem/oneup_flysystem.yml config/packages/dev/
    $ cp vendor/akeneo/pim-enterprise-dev/config/packages/prod_onprem/messenger.yml config/packages/dev/


You can then launch the install with the following command:

.. code-block:: bash

	$ NO_DOCKER=true make dev


Once this command is finished, the PIM is accessible at http://localhost:8080/

Launching the PIM in prod mode
------------------------------

.. code-block:: bash

   $ NO_DOCKER=true make prod

Once this command is finished, the PIM is accessible at http://localhost:8080/

Setup Akeneo
----------------------

Configuring Akeneo
******************

Akeneo PIM is configured with environment variables. The `Symfony documentation <https://symfony.com/doc/current/configuration.html#configuration-based-on-environment-variables>`_ explains how to use them.


Running jobs
************

Akeneo PIM implements a queue for the `jobs <../../import_and_export_data/index.html>`_, as a PHP daemon. This daemon is a Symfony command, that can only execute one job at a time. It does not consume any other job until the job is finished.

You can launch several daemons to allow the execution of several jobs in parallel. A daemon checks every 5 seconds the queue and executes the next job from the queue.

Follow the job queue daemon set up in :doc:`this dedicated section </install_pim/manual/daemon_queue>`.


Cron jobs
*********

The application needs the following tasks to be executed in background on a regular basis. The frequency has to be adapted according to your data volume.

Edit your crontab with ``crontab -e`` and configure your tasks.

.. warning::

    Be sure to update the cron of the user used to install the PIM, to be able to run the command

Community Edition and Enterprise Edition cron jobs:

+-------------------------------------------------------------------------------+-------------------+--------------------------------------------+
| Symfony console command                                                       | Crontab frequency | Human frequency                            |
+===============================================================================+===================+============================================+
| :code:`pim:versioning:refresh`                                                | 30 1 \* \* \*     | At 01:30 AM                                |
+-------------------------------------------------------------------------------+-------------------+--------------------------------------------+
| :code:`pim:versioning:purge --more-than-days 90`                              | 30 2 \* \* \*     | At 02:30 AM                                |
+-------------------------------------------------------------------------------+-------------------+--------------------------------------------+
| :code:`akeneo:connectivity-audit:update-data`                                 | 1 \* \* \* \*     | Every hour                                 |
+-------------------------------------------------------------------------------+-------------------+--------------------------------------------+
| :code:`akeneo:connectivity-connection:purge-error`                            | 10 \* \* \* \*    | Every hour                                 |
+-------------------------------------------------------------------------------+-------------------+--------------------------------------------+
| :code:`akeneo:batch:purge-job-execution`                                      | 20 0 1 \* \*      | At 12:20 AM, every first day of the month  |
+-------------------------------------------------------------------------------+-------------------+--------------------------------------------+
| :code:`akeneo:connectivity-audit:purge-error-count`                           | 40 12 \* \* \*    | At 12:40 AM                                |
+-------------------------------------------------------------------------------+-------------------+--------------------------------------------+
| :code:`pim:volume:aggregate`                                                  | 30 4 \* \* \*     | At 04:30 AM                                |
+-------------------------------------------------------------------------------+-------------------+--------------------------------------------+
| :code:`pim:data-quality-insights:schedule-periodic-tasks`                     | 15 0 \* \* \*     | At 00:15 AM                                |
+-------------------------------------------------------------------------------+-------------------+--------------------------------------------+
| :code:`pim:data-quality-insights:prepare-evaluations`                         | \*/10 \* \* \* \* | Every 10 minutes                           |
+-------------------------------------------------------------------------------+-------------------+--------------------------------------------+
| :code:`pim:data-quality-insights:evaluations`                                 | \*/30 \* \* \* \* | Every 30 minutes                           |
+-------------------------------------------------------------------------------+-------------------+--------------------------------------------+
| :code:`akeneo:messenger:doctrine:purge-messages messenger_messages default`   | 0 \*/2 \* \* \*   | Every 2 hours                              |
+-------------------------------------------------------------------------------+-------------------+--------------------------------------------+
| :code:`akeneo:connectivity-connection:purge-events-api-logs`                  | 5 \* \* \* \*     | Every hour                                 |
+-------------------------------------------------------------------------------+-------------------+--------------------------------------------+


Additional Enterprise Edition cron jobs:

+-------------------------------------------------------------+---------------------+------------------+
| Symfony console command                                     | Crontab frequency   | Human frequency  |
+=============================================================+=====================+==================+
| :code:`akeneo:rule:run`                                     | 0 5 \* \* \*        | At 05:00 AM      |
+-------------------------------------------------------------+---------------------+------------------+
| :code:`pimee:project:notify-before-due-date`                | 20 0 \* \* \*       | At 12:20 AM      |
+-------------------------------------------------------------+---------------------+------------------+
| :code:`pimee:project:recalculate`                           | 0 2 \* \* \*        | At 02:00 AM      |
+-------------------------------------------------------------+---------------------+------------------+
| :code:`akeneo:reference-entity:refresh-records`             | 0 23 \* \* \*       | At 11:00 PM      |
+-------------------------------------------------------------+---------------------+------------------+
| :code:`pimee:sso:rotate-log 30`                             | 30 2 \* \* \*       | At 02:30 AM      |
+-------------------------------------------------------------+---------------------+------------------+
