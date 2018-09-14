import program from 'commander'
import chalk from 'chalk'

var addon = require('../native');

program
    .version('0.1.0')
    .option('-r, --reps <n>', 'Number of random samples', '1000000')
    .parse(process.argv)

let reps = parseInt(program.reps)

console.log(chalk.blue('reps: ') + reps)
console.log(chalk.yellow('pi: ') + chalk.green(addon.pi(reps)))
