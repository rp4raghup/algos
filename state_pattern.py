# Example python module with state machine

class StateMachine(object):
  def __init__(self, state_list):
    self.state_list = state_list
    self.cur_state = self.create_state_machine(state_list)

  def execute(self):
    if self.cur_state == None:
      return
    print "State:", self.cur_state.name, ", Task:", self.cur_state.tasks[self.cur_state.cur_task]
    return self.next_task()

  def next_task(self):
    self.cur_state.cur_task += 1
    if self.cur_state.cur_task == len(self.cur_state.tasks):
      old_state = self.cur_state.name
      self.cur_state = self.cur_state.next()
      new_state = self.cur_state.name if self.cur_state else None
      print "Changing state: %s to %s" % (old_state, new_state)

  def create_state_machine(self, state_list):
    prev_state = None
    for state, tasks in state_list[::-1]:
      prev_state = States(state, tasks, prev_state)
    return prev_state


class States(StateMachine):
  def __init__(self, state_name, task_list, next_state):
    self.cur_task = 0
    self.name = state_name
    self.tasks = task_list
    self.next_state = next_state
    self.cur_state = self

  def next(self):
    return self.next_state

if __name__ == "__main__":
  state_list = [
      ("State1", ["State1_t1", "State1_t2", "State1_t3", "State1_t4"]),
      ("State2", ["State2_t1", "State2_t2", "State2_t3"]),
      ("State3", ["State3_t1", "State3_t2", "State3_t3", "State3_t4"])
    ]
  sm = StateMachine(state_list)
  while sm.cur_state:
    sm.execute()

"""
Output:
State: State1 , Task: State1_t1
State: State1 , Task: State1_t2
State: State1 , Task: State1_t3
State: State1 , Task: State1_t4
Changing state: State1 to State2
State: State2 , Task: State2_t1
State: State2 , Task: State2_t2
State: State2 , Task: State2_t3
Changing state: State2 to State3
State: State3 , Task: State3_t1
State: State3 , Task: State3_t2
State: State3 , Task: State3_t3
State: State3 , Task: State3_t4
Changing state: State3 to None
"""
