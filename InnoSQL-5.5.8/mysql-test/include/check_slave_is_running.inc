# ==== Purpose ====
#
# Assert that the slave threads are running and don't have any errors.
#
# ==== Usage ====
#
# --source include/check_slave_running.inc

--echo Checking that both slave threads are running.

--let $running= 1
--let $slave_sql_running = query_get_value(SHOW SLAVE STATUS, Slave_SQL_Running, 1)
--let $slave_io_running = query_get_value(SHOW SLAVE STATUS, Slave_IO_Running, 1)

if ($slave_sql_running != Yes) {
  --let $running= 0
}
if ($slave_io_running != Yes) {
  --let $running= 0
}

if (!$running) {
  --echo Slave not running: Slave_SQL_Running = $slave_sql_running Slave_IO_Running = $slave_io_running
  --source include/show_rpl_debug_info.inc
  --die Expected slave to be running, but it was not running.
}
