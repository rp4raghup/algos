# Example python module with state machine
class State(object):
  def execute(self):
    if self.cur_state == None:
      return
    print "State:", self.name, ". Task:", self.tasks[self.cur_task]
    return self.next_task()

  def next_task(self):
    self.cur_task += 1
    if self.cur_task == len(self.tasks):
      self.cur_task = 0
      self.cur_state = self.cur_state.next()
      old_state = self.name
      new_state = self.cur_state.name if self.cur_state else None
      print "Changing state: %s to %s" % (old_state, new_state)

class State_1(State):
  def __init__(self):
    self.tasks = ["State1_t1", "State1_t2", "State1_t3", "State1_t4"]
    self.cur_task = 0
    self.name = "State1"
    self.cur_state = self

  def next(self):
    return State_2()

class State_2(State):
  def __init__(self):
    self.tasks = ["State2_t1", "State2_t2", "State2_t3"]
    self.cur_task = 0
    self.name = "State2"
    self.cur_state = self

  def next(self):
    return State_3()

class State_3(State):
  def __init__(self):
    self.tasks = ["State3_t1", "State3_t2", "State3_t3", "State3_t4"]
    self.cur_task = 0
    self.name = "State3"
    self.cur_state = self

  def next(self):
    return None

s = State_1()
while s.cur_state:
  s.execute()