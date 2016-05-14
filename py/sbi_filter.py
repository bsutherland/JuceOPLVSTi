import glob
import os

class SBI:
  def __init__(self, sbi_data):
    if sbi_data[0:3] != b'SBI':
      raise ValueError('Invalid file header.')
    if len(sbi_data) != 52:
      raise ValueError('Invalid file size.')
    self.register_values = sbi_data[36:]

  def __eq__(self, other):
    return isinstance(other, SBI) and self.register_values == other.register_values

  def __hash__(self):
    return hash(self.register_values)


# Requires Python 3.5+
def find_distinct_sbis(root_dir):
  sbis = {}
  bad = []
  for filename in glob.iglob(os.path.join(root_dir, '**', '*.sbi'), recursive=True):
    with open(filename, 'rb') as f:
      try:
        sbi = SBI(f.read())
        try:
          dup_filename = sbis[sbi]
          print('Duplicate SBI file: %s (duplicate of %s)' % (filename, dup_filename))
          bad.append(filename)
        except KeyError:
          sbis[sbi] = filename
      except ValueError as e:
        print('Invalid SBI file: %s (%s)' % (filename, e))
        bad.append(filename)
  return sbis, bad


if __name__ == '__main__':
  distinct_sbis, to_delete = find_distinct_sbis('.')
  print('Found %d distinct SBI files' % len(distinct_sbis))
  print('Writing batch file..')
  with open('delete_bad_sbis.cmd', 'w') as batch_file:
    for delete in to_delete:
      print('DEL %s' % delete, file=batch_file)
